/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_integer_table.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 18:23:39 by cbaldy            #+#    #+#             */
/*   Updated: 2016/04/22 14:48:14 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sort_integer_table(int *tabl, int size)
{
	int		i[2];
	int		n;
	int		buf;

	n = 1;
	while (n != 0)
	{
		n = 0;
		i[0] = 0;
		while (i[0] < size - 1)
		{
			i[1] = i[0] + 1;
			if (tabl[i[0]] > tabl[i[1]])
			{
				buf = tabl[i[0]];
				tabl[i[0]] = tabl[i[1]];
				tabl[i[1]] = buf;
				n = 1;
			}
			i[0]++;
		}
	}
}
