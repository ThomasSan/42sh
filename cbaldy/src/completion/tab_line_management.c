/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_line_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 16:19:18 by dbaldy            #+#    #+#             */
/*   Updated: 2016/04/25 14:50:13 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	com_list_lines(t_com_list *begin)
{
	t_com_list	*tmp;
	int			count_elem;
	int			count_cr;

	tmp = begin;
	count_elem = 0;
	count_cr = 0;
	while (tmp)
	{
		count_elem++;
		if (tmp->c == '\n')
			count_cr++;
		tmp = tmp->next;
	}
	return ((count_elem / g_local->nb_col) + count_cr);
}

int			retrieve_row_to_skip(t_line_list *first)
{
	t_line_list		*tmp;
	int				row_to_skip;
	int				total_row;
	int				size_list;

	tmp = first->next;
	size_list = com_list_count(first->begin);
	total_row = size_list / g_local->nb_col;
	row_to_skip = total_row - (g_local->curs / g_local->nb_col);
	while (tmp)
	{
		row_to_skip += com_list_lines(tmp->begin);
		tmp = tmp->next;
	}
	return (row_to_skip);
}

int			place_cursor_to_completion(t_line_list *first)
{
	int		row_to_skip;

	row_to_skip = retrieve_row_to_skip(first);
	ft_notputs("do", row_to_skip);
	return (0);
}

int			go_back_to_selected_char(t_line_list *first)
{
	int		row_to_skip;

	row_to_skip = retrieve_row_to_skip(first);
	ft_notputs("up", row_to_skip + 1);
	ft_notputs("nd", g_local->curs % g_local->nb_col - 1);
	return (0);
}
