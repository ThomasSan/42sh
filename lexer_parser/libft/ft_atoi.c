/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 15:07:08 by tsanzey           #+#    #+#             */
/*   Updated: 2015/11/28 10:39:05 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int		sign;
	int		nb;
	int		val;

	sign = 1;
	nb = 0;
	val = 0;
	while (*str == ' ' || *str == '\n' || *str == '\v' || *str == '\r'
			|| *str == '\t' || *str == '\f')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nb = *str - '0';
		val = (val * 10) + nb;
		str++;
	}
	return (val * sign);
}
