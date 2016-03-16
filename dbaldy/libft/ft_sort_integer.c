/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_integer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 19:00:34 by dbaldy            #+#    #+#             */
/*   Updated: 2015/11/30 12:18:52 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_sort_integer(int *tab, size_t size)
{
	size_t	i;
	int		a;

	if (size < 2)
		return ;
	while (size--)
	{
		i = 0;
		while (i < size)
		{
			if (tab[i] > tab[i + 1])
			{
				a = tab[i + 1];
				tab[i + 1] = tab[i];
				tab[i] = a;
			}
			i++;
		}
	}
}
