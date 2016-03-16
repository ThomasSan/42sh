/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_fct2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 10:14:12 by dbaldy            #+#    #+#             */
/*   Updated: 2016/01/21 14:40:17 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_putsfx(va_list ap)
{
	unsigned int	nb;
	char			*str;

	nb = va_arg(ap, unsigned int);
	str = ft_itoa_adv(nb, "0123456789abcdef");
	return (str);
}

char		*ft_putlx(va_list ap)
{
	char				*str;
	unsigned long		nb;

	nb = va_arg(ap, unsigned long);
	str = ft_itoa_adv_u(nb, "0123456789abcdef");
	return (str);
}

char		*treat_x(char *str)
{
	const char	*padd;

	if (g_trait & OPT_DIESE && check_base(str, 16) != 0)
		return (treat_p(str));
	padd = ((g_trait & OPT_ZERO) == OPT_ZERO) ? "0" : " ";
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

char		*ft_upper(char *str)
{
	int			i;
	char		*st;

	i = 0;
	st = ft_strdup(str);
	while (str[i])
	{
		st[i] = ft_toupper(str[i]);
		i++;
	}
	free(str);
	return (st);
}

char		*get_majx(va_list ap)
{
	char	*str;

	if ((g_trait & OPT_J) == OPT_J)
		str = ft_putjx(ap);
	else if ((g_trait & OPT_Z) == OPT_Z)
		str = ft_putzx(ap);
	else if ((g_trait & OPT_LL) == OPT_LL)
		str = ft_putllx(ap);
	else if ((g_trait & OPT_L) == OPT_L)
		str = ft_putlx(ap);
	else if ((g_trait & OPT_HH) == OPT_HH)
		str = ft_puthhx(ap);
	else if ((g_trait & OPT_H) == OPT_H)
		str = ft_puthx(ap);
	else
		str = ft_putsfx(ap);
	return (str);
}
