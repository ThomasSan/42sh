/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_prime.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 19:22:48 by cbaldy            #+#    #+#             */
/*   Updated: 2015/11/30 10:38:00 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_is_prime(int nb)
{
	int	i[2];

	i[1] = 1;
	i[0] = 2;
	if (nb < 2)
		return (0);
	else if (nb == 2 || nb == 3)
		return (1);
	else
	{
		while (i[0] < nb / (i[0] - 1))
		{
			if (nb % i[0] == 0)
				i[1] = 0;
			i[0]++;
		}
		return (i[1]);
	}
}
