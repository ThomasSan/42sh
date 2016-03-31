/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yank_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 10:06:21 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/31 11:52:08 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	yank_end_line(t_com_list **begin)
{
	t_com_list	*tmp;
	int			i;

	i = g_local->prompt;
	tmp = *begin;
	while (tmp != NULL && i++ < g_local->curs - 1)
		tmp = tmp->next;
	while (tmp != NULL)
	{
		tmp->op = 2;
		tmp = tmp->next;
	}
	copy_end_mode(begin);
	while (term_mv_horizontal(3, com_list_count(*begin)) == 0)
		;
	return (0);
}

static int	yank_begin_line(t_com_list **begin)
{
	t_com_list	*tmp;
	int			i;

	i = g_local->prompt;
	tmp = *begin;
	while (tmp != NULL && i++ < g_local->curs - 1)
	{
		tmp->op = 2;
		tmp = tmp->next;
	}
	copy_end_mode(begin);
	while (term_mv_horizontal(4, 0) == 0)
		;
	return (0);
}

int			yank_line(char c, t_line_list **first)
{
	t_com_list	*tmp;
	int			i;

	if (c == 25)
		return (copy_paste(&((*first)->begin));
	i = g_local->prompt;
	tmp = *begin;
	if (c == 21)
		return (yank_end_line(begin));
	else if (c == 11)
		return (yank_begin_line(begin));
	return (0);
}
