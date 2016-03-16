/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d3_fct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/20 09:03:45 by dbaldy            #+#    #+#             */
/*   Updated: 2016/01/30 14:53:24 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	g_base[] = "0123456789abcdef";

int			size_sign(char *st)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (st[i] && (st[i] < '0' || st[i] > '9'))
		i++;
	while (st[i])
	{
		j++;
		i++;
	}
	return (j);
}

int			check_base(char *str, int base)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	if (base == 10)
		return (0);
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n')
			|| (str[i] == '\f') || (str[i] == '\r') || (str[i] == '\v')
			|| (str[i] == '0'))
		i++;
	while (g_base[j] && j < base)
	{
		if (str[i] == g_base[j])
			return (1);
		j++;
	}
	return (0);
}

char		*precision(char *str, int base)
{
	char	*tmp;
	int		i;

	i = 0;
	if (g_precision < 0 && ft_atoi(str) == 0 && check_base(str, base) == 0)
	{
		while ((str[i] < '0' || str[i] > '9') && str[i] != 0)
			i++;
		tmp = ft_strsub(str, 0, i);
		free(str);
		str = tmp;
	}
	return (str);
}

int			nombre_digit(char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		i++;
		j++;
	}
	return (j);
}
