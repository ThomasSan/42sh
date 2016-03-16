/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_fct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/10 15:29:47 by dbaldy            #+#    #+#             */
/*   Updated: 2016/01/21 14:54:15 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

char			*ft_puthhb(va_list ap)
{
	char				*str;
	unsigned char		nb;

	nb = (unsigned char)va_arg(ap, int);
	str = ft_itoa_adv(nb, "01234567");
	return (str);
}

char			*ft_puthb(va_list ap)
{
	char				*str;
	unsigned short		nb;

	nb = (unsigned short)va_arg(ap, int);
	str = ft_itoa_adv(nb, "01234567");
	return (str);
}

char			*ft_putjb(va_list ap)
{
	char				*str;
	uintmax_t			nb;

	nb = va_arg(ap, uintmax_t);
	str = ft_itoa_adv_u(nb, "01234567");
	return (str);
}

char			*ft_putllb(va_list ap)
{
	char				*str;
	unsigned long long	nb;

	nb = va_arg(ap, unsigned long long);
	str = ft_itoa_adv_u(nb, "01234567");
	return (str);
}

char			*ft_putlb(va_list ap)
{
	char				*str;
	unsigned long		nb;

	nb = va_arg(ap, unsigned long);
	str = ft_itoa_adv_u(nb, "01234567");
	return (str);
}
