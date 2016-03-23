/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_line_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 16:19:18 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/22 16:55:05 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			place_cursor_to_completion(t_com_list *begin)
{
	int		size_list;
	int		total_row;
	int		row_to_skip;

	size_list = com_list_count(begin);
	total_row = size_list / g_local->nb_col;
	row_to_skip = total_row - (g_local->curs / g_local->nb_col);
	ft_notputs("do", row_to_skip);
	return (0);
}

int			go_back_to_selected_char(t_com_list *begin)
{
	int		size_list;
	int		total_row;
	int		row_to_skip;

	size_list = com_list_count(begin);
	total_row = size_list / g_local->nb_col;
	row_to_skip = total_row - (g_local->curs / g_local->nb_col);
	ft_notputs("up", row_to_skip + 1);
	ft_notputs("nd", g_local->curs % g_local->nb_col - 1);
	return (0);
}
