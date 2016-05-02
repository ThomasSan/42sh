/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ouxprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 15:32:59 by cbaldy            #+#    #+#             */
/*   Updated: 2016/01/28 17:56:41 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_uint(va_list ap2)
{
	unsigned int	max;
	unsigned int	nb;

	if (g_op->size == 0)
		max = 2147483647;
	else if (g_op->size == 1)
		max = 256;
	else
		max = 65536;
	nb = va_arg(ap2, unsigned int);
	if (g_op->size == 0)
		return (ft_putnbr_3(nb));
	return (ft_putnbr_3(nb % max));
}

static int	ft_print_ul(va_list ap2)
{
	unsigned long	nb;

	nb = va_arg(ap2, unsigned long);
	return (ft_putnbr_3(nb));
}

static int	ft_print_ull(va_list ap2)
{
	unsigned long long	nb;

	nb = va_arg(ap2, unsigned long long);
	return (ft_putnbr_3(nb));
}

int			ft_print_uz(va_list ap2)
{
	intmax_t	nb;

	nb = va_arg(ap2, intmax_t);
	return (ft_putnbr_3(nb));
}

int			ft_ouxprint(va_list ap2)
{
	if (g_op->size < 3)
		return (ft_print_uint(ap2));
	else if (g_op->size == 3)
		return (ft_print_uz(ap2));
	else if (g_op->size == 4)
		return (ft_print_ul(ap2));
	else if (g_op->size == 5)
		return (ft_print_ull(ap2));
	else
		return (ft_print_uz(ap2));
}
