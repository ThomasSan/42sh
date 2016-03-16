/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_fct.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 13:44:37 by dbaldy            #+#    #+#             */
/*   Updated: 2016/01/30 14:53:32 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_putdc(va_list ap)
{
	char				*str;
	char				l;

	l = (char)va_arg(ap, int);
	str = ft_itoa_adv(l, "0123456789");
	return (str);
}

char		*ft_putsh(va_list ap)
{
	short	d;
	char	*str;

	d = (short)va_arg(ap, int);
	str = ft_itoa_adv(d, "0123456789");
	return (str);
}

char		*ft_puth(va_list ap)
{
	intmax_t	d;
	char		*str;

	d = va_arg(ap, intmax_t);
	str = ft_itoa_adv(d, "0123456789");
	return (str);
}

char		*ft_putsf(va_list ap)
{
	char		*str;
	int			d;

	d = va_arg(ap, int);
	str = ft_itoa_adv(d, "0123456789");
	return (str);
}

char		*treat_d(char *str)
{
	const char	*padd;

	padd = ((g_trait & OPT_ZERO) == OPT_ZERO) ? "0" : " ";
	while (size_sign(str) < g_precision)
		str = complete(str, 1, "0");
	if ((g_trait & OPT_PLUS) == OPT_PLUS && ft_atoi(str) >= 0)
		str = complete(str, 1, "+");
	if ((g_trait & OPT_SPACE) && str[0] != '-' && str[0] != '+')
		str = complete(str, 1, " ");
	while (ft_strlen(str) < g_width)
	{
		if ((g_trait & OPT_MIN) == OPT_MIN)
			str = complete_behind(str, 2, " ");
		else if (padd[0] == '0' && (str[0] > '9' || str[0] < '0'))
			str = complete_special(str, 1, padd);
		else
			str = complete(str, 1, padd);
	}
	return (str);
}
