/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 11:19:03 by cbaldy            #+#    #+#             */
/*   Updated: 2016/01/29 13:58:36 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_echar(va_list ap2)
{
	char	*s;
	char	*padd;
	int		i;

	padd = (g_op->zero == 1 ? "0" : " ");
	if ((s = va_arg(ap2, char *)) == NULL)
		s = ft_strdup("(null)");
	else
		s = ft_strdup(s);
	if (g_op->dot != 0 && g_op->precision < (int)ft_strlen(s))
		s = pf_strsub(s, 0, (int)g_op->precision, 1);
	while (g_op->width > (int)ft_strlen(s))
	{
		if (g_op->moins == 1)
			s = pf_strjoin(s, " ", 1);
		else
			s = pf_strjoin(padd, s, 2);
	}
	ft_putstr_fd(s, g_op->fd);
	i = ft_strlen(s);
	free(s);
	return (i);
}

static int	ft_null_string(void)
{
	char	*s;
	int		i;
	char	*padd;

	padd = (g_op->zero == 1 ? "0" : " ");
	s = ft_strdup("(null)");
	if (g_op->dot != 0 && g_op->precision < (int)ft_strlen(s))
		s = pf_strsub(s, 0, (int)g_op->precision, 1);
	while (g_op->width > (int)ft_strlen(s))
	{
		if (g_op->moins == 1)
			s = pf_strjoin(s, " ", 1);
		else
			s = pf_strjoin(padd, s, 2);
	}
	ft_putstr_fd(s, g_op->fd);
	i = ft_strlen(s);
	free(s);
	return (i);
}

static int	ft_print_ewchar(va_list ap2)
{
	wchar_t	*s;
	int		i[3];

	if ((s = (wchar_t *)va_arg(ap2, char *)) == NULL)
		return (ft_null_string());
	i[0] = 0;
	i[2] = 0;
	i[1] = ft_nb_printed_bytes(s);
	while (g_op->width > i[1] && g_op->moins == 0)
	{
		write(1, (g_op->zero == 1 ? "0" : " "), 1);
		i[1]++;
	}
	while (s[i[0]] != 0 && (g_op->precision >= i[2] +
				ft_nb_bytes(&(s[i[0]]), 1) || g_op->dot == 0))
	{
		i[2] += ft_conv_wchar(s[i[0]]);
		i[0]++;
	}
	while (g_op->width > i[1] && g_op->moins == 1)
	{
		write(1, " ", 1);
		i[1]++;
	}
	return (i[2] + (i[1] - ft_nb_printed_bytes(s)));
}

int			ft_sprint(va_list ap2)
{
	if (g_op->size != 4 && g_op->c != 'S')
		return (ft_print_echar(ap2));
	else
		return (ft_print_ewchar(ap2));
}
