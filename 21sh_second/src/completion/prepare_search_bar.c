/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 13:33:15 by dbaldy            #+#    #+#             */
/*   Updated: 2016/04/02 19:25:16 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int				prepare_search_bar(t_line_list **first, t_hist_list **hist)
{
	t_line_list *temoin;

	temoin = *first;
	line_list_free((*hist)->old);
	while (temoin->previous)
		temoin = temoin->previous;
	(*hist)->old = line_list_dup(temoin);
	return (0);
}
