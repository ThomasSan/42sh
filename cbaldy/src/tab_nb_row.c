/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nb_row.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 17:53:59 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/23 12:52:49 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int			clear_tparam(t_param **begin)
{
	t_param		*buf;
	t_param		*a;

	buf = *begin;
	while (buf)
	{
		a = buf->next;
		free(buf->var);
		buf->next = NULL;
		buf->prev = NULL;
		free(buf);
		buf = a;
	}
	*begin = NULL;
	return (0);
}

static int	clear_curr_compl(void)
{
	if (g_curr_compl != NULL)
	{
		clear_tparam(&(g_curr_compl->begin));
		free(g_curr_compl->var);
		free(g_curr_compl);
		g_curr_compl = NULL;
	}
	return (0);
}

int			exit_completion(t_com_list *begin)
{
	int		size_list;
	int		row_pos;
	int		row_to_skip;

	if (g_curr_compl != NULL)
	{
		size_list = com_list_count(begin);
		row_pos = g_local->curs / g_local->nb_col;
		row_to_skip = (size_list / g_local->nb_col) - row_pos;
		ft_notputs("do", row_to_skip);
		ft_notputs("cd", 1);
		clear_curr_compl();
	}
	return (0);
}

int			get_size_list(t_param *debut)
{
	t_param		*buf;
	int			nb_param;

	buf = debut->next;
	nb_param = (debut->select >= 0) ? 1 : 0;
	while (buf->nb > 0)
	{
		if (buf->select >= 0)
			nb_param++;
		buf = buf->next;
	}
	return (nb_param);
}

int			get_nb_row(t_param *debut, int nb_col)
{
	int		size_list;
	int		nb_row;

	size_list = get_size_list(debut);
	nb_row = size_list / nb_col;
	if (size_list % nb_col != 0)
		nb_row++;
	return (nb_row);
}
