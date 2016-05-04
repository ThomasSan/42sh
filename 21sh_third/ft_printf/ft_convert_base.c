/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 19:31:59 by cbaldy            #+#    #+#             */
/*   Updated: 2016/01/14 16:20:43 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_deconvert(char *nbr, char *base_from)
{
	int i[4];
	int k;

	i[0] = ft_strlen(base_from);
	i[1] = ft_strlen(nbr);
	i[2] = 0;
	k = 0;
	while (nbr[i[2]] != '\0')
	{
		i[3] = 0;
		while (base_from[i[3]] != '\0')
		{
			if (nbr[i[2]] == base_from[i[3]])
			{
				k = k + ft_power_cv(i[0], i[1] - 1 - i[2]) * i[3];
				i[3]++;
			}
			else
				i[3]++;
		}
		i[2]++;
	}
	return (k);
}

char			*ft_convert_base(char *nbr, char *base_fr, char *base_to)
{
	unsigned long long	k;

	k = ft_deconvert(nbr, base_fr);
	return (ft_reconvert(k, base_to));
}
