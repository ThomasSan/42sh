/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yank_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 10:06:21 by cbaldy            #+#    #+#             */
/*   Updated: 2016/04/02 16:07:49 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	yank_end_line(t_line_list **first)
{
	t_com_list	*tmp;
	int			i;

	tmp = (*first)->begin;
	i = (*first)->marge;
	while (tmp != NULL && i++ < g_local->curs - 1)
		tmp = tmp->next;
	while (tmp != NULL)
	{
		tmp->op = 2;
		tmp = tmp->next;
	}
	copy_end_mode(first);
	while (term_mv_horizontal(3, first) == 0)
		;
	return (0);
}

static int	yank_begin_line(t_line_list **first)
{
	t_com_list	*tmp;
	int			i;

	i = (*first)->marge;
	tmp = (*first)->begin;
	while (tmp != NULL && i++ < g_local->curs - 1)
	{
		tmp->op = 2;
		tmp = tmp->next;
	}
	copy_end_mode(first);
	while (term_mv_horizontal(4, first) == 0)
		;
	return (0);
}

int			yank_line(char c, t_line_list **first)
{
	t_com_list	*tmp;
	int			i;

	if (c == 25)
		return (copy_paste(first));
	i = (*first)->marge;
	tmp = (*first)->begin;
	if (c == 21)
		return (yank_end_line(first));
	else if (c == 11)
		return (yank_begin_line(first));
	return (0);
}
