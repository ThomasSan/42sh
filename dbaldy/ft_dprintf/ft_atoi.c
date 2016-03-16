/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 16:28:20 by dbaldy            #+#    #+#             */
/*   Updated: 2016/01/30 14:53:49 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

static int		ft_check1(const char *str)
{
	int		i;

	i = 0;
	if ((str[i] == '+' && str[i + 1] == '-') ||
			(str[i] == '-' && str[i + 1] == '+'))
		return (1);
	else
		return (0);
}

long long		ft_atoi(const char *str)
{
	size_t		i;
	int			a;
	long long	res;

	i = 0;
	a = 1;
	res = 0;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n')
		|| (str[i] == '\f') || (str[i] == '\r') || (str[i] == '\v'))
		i++;
	if (ft_check1(&str[i]))
		return (0);
	if (str[i] == '-')
	{
		a = -1;
		i++;
	}
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * a);
}
