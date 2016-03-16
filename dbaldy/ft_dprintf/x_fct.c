/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hh_fct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 11:21:56 by dbaldy            #+#    #+#             */
/*   Updated: 2016/01/21 14:38:42 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*ft_puthhx(va_list ap)
{
	char				*str;
	unsigned char		nb;

	nb = (unsigned char)va_arg(ap, int);
	str = ft_itoa_adv_u(nb, "0123456789abcdef");
	return (str);
}

char			*ft_puthx(va_list ap)
{
	char				*str;
	unsigned short		nb;

	nb = (unsigned short)va_arg(ap, int);
	str = ft_itoa_adv_u(nb, "0123456789abcdef");
	return (str);
}

char			*ft_putllx(va_list ap)
{
	char				*str;
	unsigned long long	nb;

	nb = va_arg(ap, unsigned long long);
	str = ft_itoa_adv_u(nb, "0123456789abcdef");
	return (str);
}

char			*ft_putjx(va_list ap)
{
	char				*str;
	uintmax_t			nb;

	nb = va_arg(ap, uintmax_t);
	str = ft_itoa_adv_u(nb, "0123456789abcdef");
	return (str);
}

char			*ft_putzx(va_list ap)
{
	char				*str;
	size_t				nb;

	nb = va_arg(ap, size_t);
	str = ft_itoa_adv_u(nb, "0123456789abcdef");
	return (str);
}
