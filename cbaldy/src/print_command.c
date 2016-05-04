/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 17:00:28 by cbaldy            #+#    #+#             */
/*   Updated: 2016/05/04 11:56:17 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	print_return_cursor(int len_str, t_line_list *first, int saut)
{
	int		op;

	if (saut > 0 && first->next != NULL)
	{
		ft_tputs("UP", 1, saut);
		ft_tputs("RI", 1, (g_local->curs - 2) % g_local->nb_col);
	}
	while (len_str > 0)
	{
		term_mv_horizontal(4, &first, 0);
		len_str--;
	}
	op = 0;
	while (term_mv_horizontal(3, &first, 0) == 0)
		op++;
	while (op > 0)
	{
		term_mv_horizontal(4, &first, 0);
		op--;
	}
	return (0);
}

static int	print_string(char *str)
{
	int		i;
	int		saut;

	i = 0;
	saut = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			ft_tputs("ce", 1, 0);
			saut++;
		}
		ft_putchar_fd(str[i], STDIN_FILENO);
		i++;
	}
	return (saut);
}

int			print_next(t_line_list *next)
{
	int	save;

	save = g_local->curs;
	g_local->curs = 1;
	print_command(next->begin, 0, next);
	g_local->curs = save;
	return (0);
}

int			print_command(t_com_list *new, char buf, t_line_list *first)
{
	char	*str;
	int		len_str;
	int		op;
	int		saut;

	ft_tputs("vi", 1, 0);
	op = (buf == 127 ? 0 : 1);
	str = com_list_retrieve(new);
	if (buf == 127)
		term_mv_horizontal(4, &first, 0);
	saut = print_string(str);
	len_str = ft_strlen(str);
	g_local->curs += len_str;
	if (g_local->curs % g_local->nb_col == 1 && len_str > 1)
		ft_tputs("sf", 1, 0);
	else if (g_local->curs % g_local->nb_col == 1 && len_str == 1)
		ft_tputs("sf", 1, 0);
	ft_tputs("ce", 1, 0);
	if (first->next != NULL)
		print_next(first->next);
	print_return_cursor(len_str - op, first, saut);
	free(str);
	ft_tputs("ve", 1, 0);
	return (buf);
}
