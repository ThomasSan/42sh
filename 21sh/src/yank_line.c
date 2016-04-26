/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yank_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 10:06:21 by cbaldy            #+#    #+#             */
/*   Updated: 2016/04/26 11:18:12 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	yank_end_line(t_line_list **first, char c)
{
	t_com_list	*tmp;
	int			i[3];

	i[1] = (c == 21 ? 2 : 1);
	tmp = (*first)->begin;
	i[0] = (*first)->marge;
	i[2] = g_local->curs;
	while (tmp != NULL && i[0]++ < g_local->curs - 1)
		tmp = tmp->next;
	while (tmp != NULL && tmp->c != '\n')
	{
		tmp->op = i[1];
		tmp = tmp->next;
	}
	copy_end_mode(first);
	while (term_mv_horizontal(3, first, 1) == 0 && g_local->curs < i[2])
		;
	return (0);
}

static int	yank_begin_line(t_line_list **first, char c)
{
	t_com_list	*tmp;
	int			i[3];

	i[1] = (c == 11 ? 2 : 1);
	i[0] = (*first)->marge;
	tmp = (*first)->begin;
	i[2] = g_local->curs;
	while (tmp != NULL && i[0]++ < g_local->curs - 1)
	{
		tmp->op = i[1];
		tmp = tmp->next;
	}
	copy_end_mode(first);
	while (term_mv_horizontal(3, first, 1) == 0 && g_local->curs < i[2])
		;
	return (0);
}

int			yank_line(char c, t_line_list **first)
{
	if (c == 25)
		return (copy_paste(first));
	if (c == 21 || c == 16)
		return (yank_end_line(first, c));
	else if (c == 11 || c == 8)
		return (yank_begin_line(first, c));
	return (0);
}
