/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_mv_cursor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 11:42:12 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/31 11:22:35 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	term_mv_home_end(int move, t_line_list **first)
{
	int		k;

	if (move == 72)
		k = 4;
	else
		k = 3;
	while (term_mv_horizontal(k, first) == 0)
		;
	return (0);
}

static int	term_mv_word(int move, t_line_list **first)
{
	int			i;
	t_com_list	*tmp;

	i = (*first)->marge;
	tmp = (*first)->begin;
	while (i++ != g_local->curs - 1)
		tmp = tmp->next;
	if (move == 67)
	{
		while (tmp && tmp->c > 32 && term_mv_horizontal(3, first) == 0)
			tmp = tmp->next;
		while (tmp && tmp->c < 33 && term_mv_horizontal(3, first) == 0)
			tmp = tmp->next;
	}
	else if (move == 68)
	{
		while (tmp && tmp->c > 32 && term_mv_horizontal(4, first) == 0)
			tmp = tmp->previous;
		while (tmp && tmp->c < 33 && term_mv_horizontal(4, first) == 0)
			tmp = tmp->previous;
		if (tmp == NULL)
			term_mv_horizontal(4, first);
	}
	return (0);
}

static int	term_mv_vertical(int move, t_line_list **first)
{
	int		buf;
	int		line;
	
	line = g_local->curs / (g_local->nb_col + 1);
	buf = g_local->nb_col - 1;
	if (move == 65 && line != 0)
	{
		while (term_mv_horizontal(4, first) == 0 && buf > 0)
			buf--;
	}
	else if (move == 66 && line < ((com_list_count((*first)->begin) +
					(*first)->marge) / (g_local->nb_col + 1)))
	{
		while (term_mv_horizontal(3, first) == 0 && buf > 0)
			buf--;
	}
	else
		return (-1);
	return (0);
}

int		term_mv_cursor(char buf, t_line_list **first)
{
	if (buf == 70 || buf == 72)
		return (term_mv_home_end(buf, first));
	else if (buf == 65 || buf == 66)
		term_mv_vertical(buf, first);
	else if (buf == 67 || buf == 68)
		term_mv_word(buf, first);
	return (0);
}
