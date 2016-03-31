/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_mv_horizontal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 20:03:13 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/31 18:04:51 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	term_mv_left(t_line_list **first)
{
	if ((*first)->marge == 0 && g_local->curs == 1)
	{
		*first = (*first)->previous;
		ft_tputs("UP", 1, 1);
		ft_tputs("RI", 1, ((com_list_count((*first)->begin) + (*first)->marge)
					% g_local->nb_col));
		g_local->curs = com_list_count((*first)->begin) + 1 + (*first)->marge;
	}
	if ((*first)->begin > 0 && g_local->curs % g_local->nb_col == 1)
	{
		ft_tputs("UP", 1, 1);
		ft_tputs("RI", 1, g_local->nb_col);
	}
	else
		ft_tputs("le", 1, 0);
	g_local->curs -= 1;
	return (0);
}

static int	term_mv_right_same(t_line_list **first)
{
	if (g_local->curs % g_local->nb_col == 0)
		ft_tputs("sf", 1, 0);
	else
		ft_tputs("nd", 1, 0);
	g_local->curs += 1;
	return (0);
	*first = NULL;
}

static int	term_mv_right_change(t_line_list **first)
{
	ft_tputs("sf", 1, 0);
	*first = (*first)->next;
	g_local->curs = (*first)->marge + 1;
	return (0);
}

int			term_mv_horizontal(int move, t_line_list **first)
{
	if (move == 3)
	{
		if (com_list_count((*first)->begin) > g_local->curs -
				(*first)->marge - 1)
			return (term_mv_right_same(first));
		else if ((*first)->next != NULL)
			return (term_mv_right_change(first));
		else
			return (-1);
	}
	else if (move == 4)
	{
		if (g_local->curs > (*first)->marge + 1)
			return (term_mv_left(first));
		else if ((*first)->marge == 0 && (*first)->previous != NULL)
			return (term_mv_left(first));
		else
			return (-1);
	}
	return (0);
}
