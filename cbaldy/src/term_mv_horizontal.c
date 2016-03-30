/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_mv_horizontal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 20:03:13 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/30 21:00:22 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static		term_mv_right(t_line_list **first)
{
	return (0);
	*first = NULL;
}

int			term_mv_horizontal(int move, t_line_list **first)
{
	if (move == 3 && com_list_count((*first)->begin) > g_local->curs -
				(*first)->marge - 1 || (*first)->next != NULL)
			return (term_mv_right(first));
	return (0);
	*first = 0;
	move = 0;
	/*if (move == 3 && len_list > g_local->curs -
			g_local->prompt - 1)
	{
		if (g_local->curs % g_local->nb_col == 0)
			ft_tputs("sf", 1, 0);
		else
			ft_tputs("nd", 1, 0);
		g_local->curs += 1;
	}
	else if (move == 4 && g_local->curs > g_local->prompt + 1)
	{
		if (g_local->curs % g_local->nb_col == 1)
		{
			ft_tputs("UP", 1, 1);
			ft_tputs("RI", 1, g_local->nb_col);
		}
		else
			ft_tputs("le", 1, 0);
		g_local->curs -= 1;
	}
	else
		return (-1);
	return (0);*/
}
