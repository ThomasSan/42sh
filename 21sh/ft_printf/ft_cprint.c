/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cprint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 17:48:44 by cbaldy            #+#    #+#             */
/*   Updated: 2016/02/15 10:59:55 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_put_zero(void)
{
	char	padd;
	int		i;

	padd = (g_op->zero == 1 ? '0' : ' ');
	i = 1;
	if (g_op->moins == 1)
	{
		ft_putchar_fd(0, g_op->fd);
		while (g_op->width > i)
		{
			ft_putchar_fd(' ', g_op->fd);
			i++;
		}
	}
	else
	{
		while (g_op->width > i)
		{
			ft_putchar_fd(padd, g_op->fd);
			i++;
		}
		ft_putchar_fd(0, g_op->fd);
	}
	return (i);
}

static int	ft_print_char(va_list ap2)
{
	char	c;
	char	*s;
	char	*padd;
	int		i;

	padd = (g_op->zero == 1 ? "0" : " ");
	if ((c = va_arg(ap2, int)) == 0)
		return (ft_put_zero());
	s = ft_strdup(" ");
	s[0] = c;
	i = 1;
	while (g_op->width > i)
	{
		if (g_op->moins == 1)
			s = pf_strjoin(s, " ", 1);
		else
			s = pf_strjoin(padd, s, 2);
		i++;
	}
	ft_putstr_fd(s, g_op->fd);
	i = ft_strlen(s);
	free(s);
	return (i);
}

int			ft_cprint(va_list ap2)
{
	int		i;

	if (g_op->size != 4 && g_op->c != 'C')
		return (ft_print_char(ap2));
	else
	{
		i = va_arg(ap2, int);
		return (ft_conv_wchar(i));
	}
}
