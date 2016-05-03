/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_mv_horizontal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 20:03:13 by cbaldy            #+#    #+#             */
/*   Updated: 2016/05/03 20:19:42 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** 1 = changement de ligne impossible
*/

static int	term_mv_left(t_line_list **first)
{
	int		k;

	k = -1;
	if ((*first)->marge == 0 && g_local->curs == 1)
	{
		*first = (*first)->previous;
		k = ft_tputs("UP", 1, 1);
		ft_tputs("RI", 1, ((com_list_count((*first)->begin) + (*first)->marge)
					% g_local->nb_col));
		g_local->curs = com_list_count((*first)->begin) + 1 + (*first)->marge;
	}
	if ((*first)->marge > 0 && g_local->curs % g_local->nb_col == 1)
	{
		if (k < 0)
			ft_tputs("UP", 1, 1);
		ft_tputs("RI", 1, g_local->nb_col);
	}
	else
		ft_tputs("le", 1, 0);
	g_local->curs -= 1;
	return (0);
}

static int	term_mv_right_change(t_line_list **first, int jump)
{
	if (jump < 0)
		ft_tputs("sf", 1, 0);
	*first = (*first)->next;
	g_local->curs = (*first)->marge + 1;
	return (1);
}

static int	term_mv_right_same(t_line_list **first, int change)
{
	int		jump;

	jump = -1;
	if (com_list_count((*first)->begin) == g_local->curs -
				(*first)->marge && (*first)->next != NULL && change == 1)
		return (1);
	if (g_local->curs % g_local->nb_col == 0)
		jump = ft_tputs("sf", 1, 0);
	else
		ft_tputs("nd", 1, 0);
	g_local->curs += 1;
	if (com_list_count((*first)->begin) == g_local->curs -
				(*first)->marge - 1 && (*first)->next != NULL)
		term_mv_right_change(first, jump);
	return (0);
}

int			term_mv_horizontal(int move, t_line_list **first, int change)
{
	if (move == 3)
	{
		if (com_list_count((*first)->begin) > g_local->curs -
				(*first)->marge - 1)
			return (term_mv_right_same(first, change));
		else if ((*first)->next != NULL && change != 1)
			return (term_mv_right_change(first, -1));
		else
			return (-1);
	}
	else if (move == 4)
	{
		if (g_local->curs > (*first)->marge + 1)
			return (term_mv_left(first));
		else if ((*first)->marge == 0 && (*first)->previous != NULL
				&& change != 1)
			return (term_mv_left(first));
		else
			return (-1);
	}
	return (0);
}
