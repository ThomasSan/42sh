/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_fct.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 16:50:20 by dbaldy            #+#    #+#             */
/*   Updated: 2016/01/30 15:17:29 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_putu(va_list ap)
{
	char		*str;

	if (g_trait & OPT_J)
		str = putuj(ap);
	else if (g_trait & OPT_Z)
		str = putuz(ap);
	else if (g_trait & OPT_LL)
		str = putull(ap);
	else if (g_trait & OPT_L)
		str = putul(ap);
	else if (g_trait & OPT_HH)
		str = putuhh(ap);
	else if (g_trait & OPT_H)
		str = putuh(ap);
	else
		str = putusf(ap);
	str = precision(str, 10);
	str = treat_u(str);
	g_print += ft_strlen(str);
	ft_putstr_fd(str, g_fd);
	free(str);
}

char		*treat_u(char *str)
{
	const char *padd;

	padd = (g_trait & OPT_ZERO) ? "0" : " ";
	while (ft_strlen(str) < g_precision)
		str = complete(str, 1, "0");
	while (ft_strlen(str) < g_width)
	{
		if (g_trait & OPT_MIN)
			str = complete_behind(str, 2, " ");
		else
			str = complete(str, 1, padd);
	}
	return (str);
}

char		*putusf(va_list ap)
{
	unsigned int	nb;
	char			*str;

	nb = va_arg(ap, unsigned int);
	str = ft_itoa_adv(nb, "0123456789");
	return (str);
}

char		*putuz(va_list ap)
{
	size_t			nb;
	char			*str;

	nb = va_arg(ap, size_t);
	str = ft_itoa_adv_u(nb, "0123456789");
	return (str);
}
