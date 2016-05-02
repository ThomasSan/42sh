/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 10:33:20 by cbaldy            #+#    #+#             */
/*   Updated: 2015/11/30 19:16:17 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static long	ft_power_nb(int p)
{
	int		j;
	long	nb;

	j = 0;
	nb = 1;
	while (j < p)
	{
		nb *= 10;
		j++;
	}
	return (nb);
}

void		ft_putnbr(int n)
{
	int		i[2];
	int		nb;

	i[1] = 0;
	if (n == 0)
		write(1, "0", 1);
	else if (n == -2147483648)
		write(1, "-2147483648", 12);
	else
	{
		if (n < 0)
		{
			write(1, "-", 1);
			n = -n;
		}
		while (n / ft_power_nb(i[1]) > 0)
			i[1]++;
		while (i[1] > 0)
		{
			nb = (n / ft_power_nb(i[1] - 1)) + 48;
			write(1, &nb, 1);
			n = n - ((n / ft_power_nb(i[1] - 1)) * ft_power_nb(i[1] - 1));
			i[1]--;
		}
	}
}
