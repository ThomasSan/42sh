/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_fct.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 15:56:37 by dbaldy            #+#    #+#             */
/*   Updated: 2016/01/30 15:16:51 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*treat_k(char *str)
{
	char	*tmp;
	char	*buf;

	buf = ft_strsub(str, 0, ft_strlen(str) - 14);
	tmp = ft_strjoin(buf, ft_strrchr(str, ' '));
	free(str);
	str = tmp;
	free(buf);
	return (str);
}

void			ft_putk(va_list ap)
{
	time_t			temps;
	char			*str;
	char			*tmp;

	temps = (const time_t)va_arg(ap, unsigned long);
	str = ctime(&temps);
	tmp = ft_strsub(str, 0, ft_strlen(str) - 1);
	str = tmp;
	if (g_trait & OPT_DIESE)
		str = treat_k(str);
	str = format_s(str);
	g_print += ft_strlen(str);
	ft_putstr_fd(str, g_fd);
	free(str);
}
