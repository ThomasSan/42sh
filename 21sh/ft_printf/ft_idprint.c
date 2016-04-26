/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_idprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/10 18:53:03 by cbaldy            #+#    #+#             */
/*   Updated: 2016/01/28 17:55:36 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_int(va_list ap2)
{
	int		max;
	int		nb;
	int		k;

	nb = va_arg(ap2, int);
	if (g_op->size == 0)
		return (ft_putnbr_2(nb));
	if (g_op->size == 1)
		max = 127;
	else
		max = 32767;
	k = nb % (2 * max + 2);
	if (k < -max - 1)
		k = k - (-max - 2) + max;
	if (k > max)
		k = k - 2 * max - 2;
	return (ft_putnbr_2(k));
}

static int	ft_print_l(va_list ap2)
{
	long	nb;

	nb = va_arg(ap2, long);
	return (ft_putnbr_2(nb));
}

static int	ft_print_ll(va_list ap2)
{
	long long	nb;

	nb = va_arg(ap2, long long);
	return (ft_putnbr_2(nb));
}

int			ft_print_z(va_list ap2)
{
	intmax_t	nb;

	nb = va_arg(ap2, intmax_t);
	return (ft_putnbr_2(nb));
}

int			ft_idprint(va_list ap2)
{
	if (g_op->size < 3)
		return (ft_print_int(ap2));
	else if (g_op->size == 3)
		return (ft_print_z(ap2));
	else if (g_op->size == 4)
		return (ft_print_l(ap2));
	else if (g_op->size == 5)
		return (ft_print_ll(ap2));
	else
		return (ft_print_z(ap2));
}
