/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_fct.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 16:49:38 by dbaldy            #+#    #+#             */
/*   Updated: 2016/01/30 15:17:14 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_putp(va_list ap)
{
	char					*str;
	unsigned long long		nb;

	nb = va_arg(ap, unsigned long long);
	str = ft_itoa_adv_u(nb, "0123456789abcdef");
	if ((g_trait & OPT_DIESE) != OPT_DIESE)
		g_trait += OPT_DIESE;
	if (check_base(str, 16) == 0 && g_precision < 0)
	{
		free(str);
		str = ft_strdup("");
	}
	str = treat_p(str);
	g_print += ft_strlen(str);
	ft_putstr_fd(str, g_fd);
	free(str);
}

char		*treat_p(char *str)
{
	const char	*padd;

	if ((g_trait & OPT_MIN) != 0 || (g_trait & OPT_ZERO) != 0)
		g_width = g_width - 2;
	padd = ((g_trait & OPT_ZERO) == OPT_ZERO) ? "0" : " ";
	while (ft_strlen(str) < g_precision)
		str = complete(str, 1, "0");
	if (ft_strcmp(padd, " ") == 0 && (g_trait & OPT_MIN) == 0)
		str = complete(str, 1, "0x");
	while (ft_strlen(str) < g_width)
	{
		if ((g_trait & OPT_MIN) == OPT_MIN)
			str = complete_behind(str, 2, " ");
		else
			str = complete(str, 1, padd);
	}
	if (ft_strcmp(padd, " ") != 0 || (g_trait & OPT_MIN) != 0)
		str = complete(str, 1, "0x");
	return (str);
}
