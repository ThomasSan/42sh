/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_mode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 13:40:47 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/18 14:05:43 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			tab_mode(t_com_list *begin)
{
	t_com_list	*tmp;
	int			i;

	if (begin == NULL)
		return (0);
	return (0);
	tmp = begin;
	i = 0;
	while (tmp->previous != NULL)
	{
		if (tmp->c == ' ')
			i = 1;
		tmp = tmp->previous;
	}
	
}
