/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 19:31:59 by cbaldy            #+#    #+#             */
/*   Updated: 2015/12/05 10:34:38 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		ft_power_cv(int nb, int power_cv)
{
	int i;

	if (power_cv < 0)
		return (0);
	else
	{
		i = 1;
		while (power_cv > 0)
		{
			i = nb * ft_power_cv(nb, power_cv - 1);
			power_cv = 0;
		}
		return (i);
	}
}

static int		ft_strrlen(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

static int		ft_deconvert(char *nbr, char *base_from)
{
	int i[4];
	int k;

	i[0] = ft_strrlen(base_from);
	i[1] = ft_strrlen(nbr);
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

static char		*ft_reconvert(int nbr, char *base_to)
{
	int		i[5];
	char	*ptr;

	i[1] = 1;
	i[0] = ft_strrlen(base_to);
	while ((nbr / i[0]) >= ft_strrlen(base_to))
	{
		i[1]++;
		i[0] = i[0] * ft_strrlen(base_to);
	}
	ptr = malloc(sizeof(char) * i[1] + 2);
	ptr[0] = base_to[nbr / ft_power_cv(ft_strrlen(base_to), i[1])];
	i[3] = 1;
	while (i[1] > 0)
	{
		i[4] = nbr / ft_power_cv(ft_strrlen(base_to), i[1] - 1);
		ptr[i[3]] = base_to[i[4] % ft_strrlen(base_to)];
		i[1]--;
		i[3]++;
	}
	ptr[i[3]] = '\0';
	return (ptr);
}

char			*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	int		k;

	k = ft_deconvert(nbr, base_from);
	return (ft_reconvert(k, base_to));
}
