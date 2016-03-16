/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nb_row.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 17:53:59 by dbaldy            #+#    #+#             */
/*   Updated: 2016/02/25 18:22:09 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

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
