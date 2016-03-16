/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u2_fct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 15:28:22 by dbaldy            #+#    #+#             */
/*   Updated: 2016/01/18 15:46:51 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*putuj(va_list ap)
{
	uintmax_t		nb;
	char			*str;

	nb = va_arg(ap, uintmax_t);
	str = ft_itoa_adv_u(nb, "0123456789");
	return (str);
}

char		*putull(va_list ap)
{
	unsigned long long	nb;
	char				*str;

	nb = va_arg(ap, unsigned long long);
	str = ft_itoa_adv_u(nb, "0123456789");
	return (str);
}

char		*putul(va_list ap)
{
	unsigned long	nb;
	char			*str;

	nb = va_arg(ap, unsigned long);
	str = ft_itoa_adv_u(nb, "0123456789");
	return (str);
}

char		*putuhh(va_list ap)
{
	unsigned char	nb;
	char			*str;

	nb = (unsigned char)va_arg(ap, unsigned int);
	str = ft_itoa_adv_u(nb, "0123456789");
	return (str);
}

char		*putuh(va_list ap)
{
	unsigned short	nb;
	char			*str;

	nb = (unsigned short)va_arg(ap, unsigned int);
	str = ft_itoa_adv_u(nb, "0123456789");
	return (str);
}
