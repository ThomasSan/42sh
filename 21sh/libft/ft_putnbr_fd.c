/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 10:33:20 by cbaldy            #+#    #+#             */
/*   Updated: 2015/11/30 19:16:30 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static long		ft_power_fd(int p)
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

void			ft_putnbr_fd(int n, int fd)
{
	int		i[2];
	int		nb;

	i[1] = 0;
	if (n == 0)
		write(fd, "0", 1);
	else if (n == -2147483648)
		write(fd, "-2147483648", 12);
	else
	{
		if (n < 0)
		{
			write(fd, "-", 1);
			n = -n;
		}
		while (n / ft_power_fd(i[1]) > 0)
			i[1]++;
		while (i[1] > 0)
		{
			nb = (n / ft_power_fd(i[1] - 1)) + 48;
			write(fd, &nb, 1);
			n -= ((n / ft_power_fd(i[1] - 1)) * ft_power_fd(i[1] - 1));
			i[1]--;
		}
	}
}
