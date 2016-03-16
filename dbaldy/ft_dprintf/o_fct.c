/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_fct.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 16:51:28 by dbaldy            #+#    #+#             */
/*   Updated: 2016/01/30 15:17:03 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_putloo(va_list ap)
{
	char				*str;

	if ((g_trait & OPT_J) == OPT_J)
		str = ft_putjo(ap);
	else if (g_trait & OPT_Z)
		str = ft_putzo(ap);
	else if ((g_trait & OPT_LL) == OPT_LL)
		str = ft_putllo(ap);
	else if ((g_trait & OPT_L) == OPT_L)
		str = ft_putlo(ap);
	else if ((g_trait & OPT_HH) == OPT_HH)
		str = ft_puthho(ap);
	else if ((g_trait & OPT_H) == OPT_H)
		str = ft_putho(ap);
	else
		str = ft_putosf(ap);
	str = precision(str, 8);
	if (ft_strcmp(str, "") == 0 && g_trait & OPT_DIESE)
		str = ft_strdup("0");
	str = treat_o(str);
	g_print += ft_strlen(str);
	ft_putstr_fd(str, g_fd);
	free(str);
}

char		*treat_o(char *str)
{
	const char		*padd;

	padd = ((g_trait & OPT_ZERO) == OPT_ZERO) ? "0" : " ";
	if ((g_trait & OPT_DIESE) == OPT_DIESE && check_base(str, 8) != 0)
		g_precision = (ft_strlen(str) >= g_precision) ? ft_strlen(str) + 1 :
			g_precision;
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

char		*ft_putzo(va_list ap)
{
	size_t			nb;
	char			*str;

	nb = va_arg(ap, size_t);
	str = ft_itoa_adv_u(nb, "01234567");
	return (str);
}

char		*ft_putosf(va_list ap)
{
	unsigned int	nb;
	char			*str;

	nb = va_arg(ap, unsigned int);
	str = ft_itoa_adv(nb, "01234567");
	return (str);
}
