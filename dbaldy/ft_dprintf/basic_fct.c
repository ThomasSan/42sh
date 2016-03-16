/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_fct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/10 15:29:47 by dbaldy            #+#    #+#             */
/*   Updated: 2016/02/08 16:39:25 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

void			ft_putint(va_list ap)
{
	char		*str;

	if ((g_trait & OPT_J) == OPT_J)
		str = ft_putj(ap);
	else if ((g_trait & OPT_Z) == OPT_Z)
		str = ft_putzd(ap);
	else if ((g_trait & OPT_LL) == OPT_LL)
		str = ft_putllg(ap);
	else if ((g_trait & OPT_L) == OPT_L)
		str = ft_putlg(ap);
	else if ((g_trait & OPT_HH) == OPT_HH)
		str = ft_putdc(ap);
	else if ((g_trait & OPT_H) == OPT_H)
		str = ft_putsh(ap);
	else
		str = ft_putsf(ap);
	str = precision(str, 10);
	str = treat_d(str);
	g_print += ft_strlen(str);
	ft_putstr_fd(str, g_fd);
	free(str);
}

void			ft_puts(va_list ap)
{
	char	*str;
	char	*res;

	if (g_trait & OPT_L || g_trait & OPT_LL)
	{
		get_winch(ap);
		return ;
	}
	res = va_arg(ap, char *);
	if (res == NULL && g_precision >= 0)
		str = ft_strdup("(null)");
	else if (res == NULL && g_width > 0 && (g_trait & OPT_ZERO) != 0)
		str = fill_str();
	else
		str = ft_strdup(res);
	str = format_s(str);
	g_print += ft_strlen(str);
	ft_putstr_fd(str, g_fd);
	free(str);
}

void			ft_putx(va_list ap)
{
	char				*str;

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
	str = precision(str, 16);
	str = treat_x(str);
	g_print += ft_strlen(str);
	ft_putstr_fd(str, g_fd);
	free(str);
}

void			ft_putmajx(va_list ap)
{
	char				*str;

	str = get_majx(ap);
	str = precision(str, 16);
	str = treat_x(str);
	str = ft_upper(str);
	g_print += ft_strlen(str);
	ft_putstr_fd(str, g_fd);
	free(str);
}
