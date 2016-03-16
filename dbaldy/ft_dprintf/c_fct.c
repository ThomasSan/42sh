/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_fct.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 12:23:25 by dbaldy            #+#    #+#             */
/*   Updated: 2016/01/30 14:59:04 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			ft_putc(va_list ap)
{
	char			*str;
	int				padd;

	if ((g_trait & OPT_L) == OPT_L || (g_trait & OPT_LL) == OPT_LL)
		str = long_char(ap);
	else
		str = get_char(ap);
	if (str[0] == 0 && g_trait & OPT_MIN)
	{
		treat_nul();
		free(str);
		return ;
	}
	padd = (str[0] == 0) ? 1 : 0;
	str = treat_c(str);
	g_print = (ft_strlen(str) > 0) ? g_print + ft_strlen(str) + padd :
		g_print + 1;
	write(g_fd, &str[0], ft_strlen(str) + padd);
	free(str);
}

char			*get_char(va_list ap)
{
	char	c;
	char	*str;

	if ((str = (char*)malloc(sizeof(char) * 2)) == NULL)
		exit(1);
	str[1] = '\0';
	c = (char)va_arg(ap, int);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

char			*long_char(va_list ap)
{
	wint_t	c;
	char	*str;
	int		i;

	i = 1;
	c = va_arg(ap, wint_t);
	str = treatwint(c);
	return (str);
}

char			*treat_c(char *str)
{
	char	*padd;
	int		i;

	i = 1;
	g_width = (str[0] == '\0') ? g_width - 1 : g_width;
	padd = ((g_trait & OPT_ZERO) == OPT_ZERO) ? "0" : " ";
	while (ft_strlen(str) < g_width)
	{
		if ((g_trait & OPT_MIN) == OPT_MIN)
			str = complete_behind(str, 2, " ");
		else
			str = complete(str, 1, padd);
		i++;
	}
	return (str);
}

void			treat_nul(void)
{
	int		i;

	i = 1;
	write(g_fd, "\0", 1);
	g_print++;
	while (i < g_width)
	{
		write(g_fd, " ", 1);
		i++;
		g_print++;
	}
}
