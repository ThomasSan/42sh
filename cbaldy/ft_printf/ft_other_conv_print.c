/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other_conv_print.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 11:20:19 by cbaldy            #+#    #+#             */
/*   Updated: 2016/01/29 15:12:46 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_percentprint(va_list ap2)
{
	char	*s;
	char	*padd;
	int		i;

	va_arg(ap2, int);
	padd = (g_op->zero == 1 ? "0" : " ");
	s = ft_strdup("%");
	while (g_op->width > (int)ft_strlen(s))
	{
		if (g_op->moins == 1)
			s = pf_strjoin(s, " ", 1);
		else
			s = pf_strjoin(padd, s, 2);
	}
	i = ft_strlen(s);
	ft_putstr_fd(s, g_op->fd);
	free(s);
	return (i);
}

static int	ft_pputnbr(unsigned long nb)
{
	char			*s[2];

	s[0] = ft_reconvert(nb, "0123456789abcdef");
	if (g_op->precision == 0 && g_op->dot == 1 && nb == 0)
		s[0][0] = '\0';
	while (g_op->precision > (int)ft_strlen(s[0]))
		s[0] = pf_strjoin("0", s[0], 2);
	s[0] = pf_strjoin("0x", s[0], 2);
	while (g_op->width > (int)ft_strlen(s[0]))
	{
		if (g_op->moins == 1)
			s[0] = pf_strjoin(s[0], " ", 1);
		else
		{
			s[1] = s[0];
			s[0] = (g_op->zero == 1 && g_op->dot == 0 ? pf_strjoin(
						pf_strjoin("0x", "0", 0), &(s[0][2]), 0) :
					pf_strjoin(" ", s[0], 0));
			free(s[1]);
		}
	}
	ft_putstr_fd(s[0], g_op->fd);
	nb = (long)ft_strlen(s[0]);
	free(s[0]);
	return (nb);
}

int			ft_pprint(va_list ap2)
{
	unsigned long	nb;

	nb = va_arg(ap2, unsigned long);
	return (ft_pputnbr(nb));
}

int			ft_invalid_conv(char *str, int i, int fd)
{
	t_op	*op;
	char	*s;
	char	*padd;
	int		p;
	char	*options;

	options = ". 1234567890#+-hljz%";
	if (ft_strchr(options, str[i + ft_len_opt(&(str[i])) - 1]) != NULL)
		return (0);
	op = ft_read_option(str, i);
	s = pf_strsub(&(str[i]), ft_len_opt(&(str[i])) - 1, 1, 0);
	padd = (op->zero == 1 ? "0" : " ");
	while (op->width > (int)ft_strlen(s))
	{
		if (op->moins == 1)
			s = pf_strjoin(s, " ", 1);
		else
			s = pf_strjoin(padd, s, 2);
	}
	ft_putstr_fd(s, fd);
	p = ft_strlen(s);
	free(s);
	free(op);
	return (p);
}
