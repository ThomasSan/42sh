/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_fct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/10 15:29:47 by dbaldy            #+#    #+#             */
/*   Updated: 2016/01/31 12:49:58 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*ft_putllg(va_list ap)
{
	long long		d;
	char			*str;

	d = va_arg(ap, long long);
	str = ft_itoa_adv(d, "0123456789");
	return (str);
}

char			*ft_putlg(va_list ap)
{
	long			d;
	char			*str;

	d = (long)va_arg(ap, long);
	str = ft_itoa_adv(d, "0123456789");
	return (str);
}

char			*ft_putj(va_list ap)
{
	intmax_t		d;
	char			*str;

	d = va_arg(ap, intmax_t);
	str = ft_itoa_adv(d, "0123456789");
	return (str);
}

char			*ft_putzd(va_list ap)
{
	size_t			nb;
	char			*str;

	nb = va_arg(ap, size_t);
	str = ft_itoa_adv(nb, "0123456789");
	return (str);
}

char			*treat_d2(char *str)
{
	char		*st;

	st = ft_strdup(str);
	free(str);
	if (size_sign(st) < g_precision && (g_trait & OPT_ZERO) == OPT_ZERO)
		st = complete(st, g_precision - ft_strlen(st), "0");
	else if (size_sign(st) < g_precision && (g_trait & OPT_MIN) != OPT_MIN)
		st = complete(st, g_precision - ft_strlen(st), " ");
	else if (size_sign(st) < g_precision && (g_trait & OPT_MIN) == OPT_MIN)
		st = complete_behind(st, g_precision - size_sign(st), " ");
	if ((g_trait & OPT_SPACE) == OPT_SPACE && st[0] != '-' && st[0] != '+')
	{
		str = st;
		st = ft_strjoin(" ", st);
		free(str);
	}
	return (st);
}
