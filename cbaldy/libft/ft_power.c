/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 18:52:08 by cbaldy            #+#    #+#             */
/*   Updated: 2015/11/29 19:15:26 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_power(int nb, int power)
{
	int		k;
	int		num;

	k = 1;
	num = nb;
	if (power == 0)
		return (1);
	while (k < power)
	{
		num = num * nb;
		k++;
	}
	return (num);
}
