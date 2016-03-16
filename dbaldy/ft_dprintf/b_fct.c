/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_fct.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 16:51:28 by dbaldy            #+#    #+#             */
/*   Updated: 2016/01/30 15:15:15 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_putb(va_list ap)
{
	char				*str;

	if ((g_trait & OPT_J) == OPT_J)
		str = ft_putjb(ap);
	else if (g_trait & OPT_Z)
		str = ft_putzb(ap);
	else if ((g_trait & OPT_LL) == OPT_LL)
		str = ft_putllb(ap);
	else if ((g_trait & OPT_L) == OPT_L)
		str = ft_putlb(ap);
	else if ((g_trait & OPT_HH) == OPT_HH)
		str = ft_puthhb(ap);
	else if ((g_trait & OPT_H) == OPT_H)
		str = ft_puthb(ap);
	else
		str = ft_putbsf(ap);
	str = precision(str, 2);
	if (ft_strcmp(str, "") == 0 && g_trait & OPT_DIESE)
		str = ft_strdup("0");
	str = treat_b(str);
	g_print += ft_strlen(str);
	ft_putstr_fd(str, g_fd);
	free(str);
}

char		*treat_b(char *str)
{
	const char		*padd;

	padd = ((g_trait & OPT_ZERO) == OPT_ZERO) ? "0" : " ";
	if ((g_trait & OPT_DIESE) == OPT_DIESE && check_base(str, 8) != 0)
		treat_b_diese(str);
	while (ft_strlen(str) < g_precision)
		str = complete(str, 1, "0");
	while (ft_strlen(str) < g_width)
	{
		if ((g_trait & OPT_MIN) == OPT_MIN)
			str = complete_behind(str, 2, " ");
		else
			str = complete(str, 1, padd);
	}
	return (str);
}

char		*treat_b_diese(char *str)
{
	const char	*padd;

	if ((g_trait & OPT_MIN) != 0 || (g_trait & OPT_ZERO) != 0)
		g_width = g_width - 2;
	padd = ((g_trait & OPT_ZERO) == OPT_ZERO) ? "0" : " ";
	while (ft_strlen(str) < g_precision)
		str = complete(str, 1, "0");
	if (ft_strcmp(padd, " ") == 0 && (g_trait & OPT_MIN) == 0)
		str = complete(str, 1, "0b");
	while (ft_strlen(str) < g_width)
	{
		if ((g_trait & OPT_MIN) == OPT_MIN)
			str = complete_behind(str, 2, " ");
		else
			str = complete(str, 1, padd);
	}
	if (ft_strcmp(padd, " ") != 0 || (g_trait & OPT_MIN) != 0)
		str = complete(str, 1, "0b");
	return (str);
}

char		*ft_putzb(va_list ap)
{
	size_t			nb;
	char			*str;

	nb = va_arg(ap, size_t);
	str = ft_itoa_adv_u(nb, "01");
	return (str);
}

char		*ft_putbsf(va_list ap)
{
	unsigned int	nb;
	char			*str;

	nb = va_arg(ap, unsigned int);
	str = ft_itoa_adv(nb, "01");
	return (str);
}
