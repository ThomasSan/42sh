/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_write_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 12:47:39 by cbaldy            #+#    #+#             */
/*   Updated: 2016/04/22 16:53:35 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	ed_add_char(t_line_list **first, char buf)
{
	t_com_list	*new;

	if ((new = com_list_new(buf)) == NULL)
		return (-1);
	com_list_add(&((*first)->begin), new, (*first)->marge);
	print_command(new, buf, *first);
	return (buf);
}

static int	ed_delete_char_nl(t_line_list **first)
{
	t_com_list	*tmp;
	t_line_list	*buf[2];

	buf[0] = (*first)->previous;
	buf[1] = (*first)->next;
	tmp = buf[0]->begin;
	while (tmp->next != NULL)
		tmp = tmp->next;
	term_mv_horizontal(4, first, 0);
	ft_tputs("cd", 1, 0);
	(*first) = (*first)->next;
	tmp->next = (*first)->begin;
	if ((*first)->begin != NULL)
		(*first)->begin->previous = tmp;
	free(*first);
	buf[0]->next = buf[1];
	if (buf[1] != NULL)
		buf[1]->previous = buf[0];
	*first = buf[0];
	print_command(tmp->next, 0, *first);
	if (tmp->next != NULL)
		term_mv_horizontal(4, first, 0);
	com_list_remove(tmp, &(buf[0]->begin));
	return (0);
}

static int	ed_delete_char(t_line_list **first)
{
	t_com_list	*tmp;
	int			i;

	if (g_local->curs == 1 && (*first)->previous != NULL)
		return (ed_delete_char_nl(first));
	if ((g_local->curs == (*first)->marge + 1 && (*first)->marge > 0) ||
			com_list_count((*first)->begin) == 0)
		return (0);
	i = 0;
	tmp = (*first)->begin;
	while (tmp->next != NULL && i < g_local->curs - (*first)->marge - 2)
	{
		tmp = tmp->next;
		i++;
	}
	print_command(tmp->next, 127, *first);
	com_list_remove(tmp, &((*first)->begin));
	return (0);
}

static int	ed_finish_line(t_line_list **first, t_hist_list **hist)
{
	int			i;
	t_line_list	*second;

	while (term_mv_horizontal(3, first, 0) != -1)
		;
	if ((i = term_finish_line(*first)) < 0)
	{
		ed_add_char(first, '\n');
		second = line_list_new(ft_dprintf(STDIN_FILENO, "new_line> "));
		second->previous = *first;
		(*first)->next = second;
		*first = second;
		g_local->curs = 11;
		clear_hist(hist);
		*hist = retrieve_history(2, NULL);
		return (0);
	}
	ft_putchar_fd('\n', STDIN_FILENO);
	return (10);
}

int			term_write_line(t_line_list **first, char buf, t_hist_list **hist)
{
	if (buf == 127)
		return (ed_delete_char(first));
	else if (buf == 10)
		return (ed_finish_line(first, hist));
	else if (buf > 31 && buf < 127)
		return (ed_add_char(first, buf));
	return (0);
}
