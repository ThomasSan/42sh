/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 14:35:13 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/31 12:11:05 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	copy_print_char(char c, int flag)
{
	if (flag != 0)
		ft_tputs("mr", 1, 0);
	ft_putchar_fd(c, STDIN_FILENO);
	ft_tputs("le", 1, 0);
	if (flag != 0)
		ft_tputs("me", 1, 0);
	return (0);
}

static int	copy_mv_cursor(int *arr, char *buf, t_com_list *tmp,
		t_line_list **first)
{
	if (g_local->curs <= arr[1] && buf[2] == 68)
		return (0);
	if (term_mv_horizontal(buf[2] - 64, first) == -1)
		return (0);
	if (buf[2] == 67 && tmp->next != NULL)
	{
		tmp->next->op ^= arr[2];
		copy_print_char(tmp->next->c, tmp->next->op);
	}
	if (buf[2] == 68)
	{
		ft_tputs("nd", 1, 0);
		tmp->op ^= arr[2];
		copy_print_char(tmp->c, tmp->op);
		ft_tputs("le", 1, 0);
	}
	return (0);
}

static int	copy_interpret(int *arr, char *buf, t_com_list *tmp)
{
	if (buf[0] == 27 && buf[1] == 91 && (buf[2] == 67 ||
				buf[2] == 68))
		return (copy_mv_cursor(arr, buf, tmp));
	else if (arr[2] == 1 && buf[0] == -61 && buf[1] == -89)
		return (1);
	else if (arr[2] == 2 && buf[0] == -30 && buf[1] == -119 && buf[2] == -120)
		return (2);
	return (0);
}

static int	copy_read(t_line_list **first, int *arr)
{
	int			i[2];
	char		buf[10];
	t_com_list	*tmp;

	i[1] = (*first)->marge;
	tmp = begin;
	while (i[1]++ != g_local->curs - 1 && tmp->next != NULL)
		tmp = tmp->next;
	read(STDIN_FILENO, buf, 9);
	i[0] = copy_interpret(arr, buf, tmp);
	return (i[0]);
}

int			copy_cut_mode(t_line_list **first, int mode)
{
	int			arr[3];
	t_com_list	*tmp;

	arr[0] = com_list_count((*first)->begin);
	arr[1] = (*first)->marge;
	arr[2] = (mode == -30 ? 2 : 1);
	tmp = *begin;
	while (arr[1]++ != g_local->curs - 1 && tmp != NULL)
		tmp = tmp->next;
	if (tmp == NULL)
		return (0);
	tmp->op ^= arr[2];
	copy_print_char(tmp->c, tmp->op);
	while (42)
	{
		if (copy_read(first, arr) != 0)
			return (copy_end_mode(first));
	}
	return (0);
}
