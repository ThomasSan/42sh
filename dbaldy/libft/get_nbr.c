/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nbr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 09:25:12 by dbaldy            #+#    #+#             */
/*   Updated: 2016/01/27 17:05:31 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			*get_nbr(char **tab)
{
	int			i;
	int			*res;
	int			atoi;

	i = 0;
	while (tab[i] != NULL)
		i++;
	if ((res = (int*)malloc(sizeof(int) * i)) == NULL)
		exit(1);
	i = 0;
	while (tab[i] != NULL)
	{
		atoi = ft_atoi(tab[i]);
		res[i] = atoi;
		i++;
	}
	return (res);
}

int			*ft_copytab(int *src, int size)
{
	int		*res;
	int		i;

	i = 0;
	if ((res = (int*)malloc(sizeof(int) * size)) == NULL)
		exit(1);
	while (i < size)
	{
		res[i] = src[i];
		i++;
	}
	return (res);
}

int			max_tab(int **tab, int x, int y)
{
	int		i;
	int		j;
	int		max;

	i = 1;
	max = 0;
	while (i < y + 1)
	{
		j = 0;
		while (j < x)
		{
			if (tab[i][j] > max)
				max = tab[i][j];
			j++;
		}
		i++;
	}
	return (max);
}

int			min_tab(int **tab, int x, int y)
{
	int		i;
	int		j;
	int		min;

	i = 1;
	min = 0;
	while (i < y + 1)
	{
		j = 0;
		while (j < x)
		{
			if (tab[i][j] < min)
				min = tab[i][j];
			j++;
		}
		i++;
	}
	return (min);
}
