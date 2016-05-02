/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_adv_putnbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 19:56:02 by cbaldy            #+#    #+#             */
/*   Updated: 2016/01/29 13:55:19 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_conv		g_base[] = {
	{'o', "01234567"},
	{'x', "0123456789abcdef"},
	{'X', "0123456789ABCDEF"},
	{'u', "0123456789"},
};

static char	*ft_padding_oux(char *nbr, unsigned long long k)
{
	char	*padd;
	char	*tmp;

	padd = (g_op->zero == 1 && g_op->dot == 0 ? "0" : " ");
	while (g_op->width > (int)ft_strlen(nbr))
	{
		if (g_op->moins == 1)
			nbr = pf_strjoin(nbr, " ", 1);
		else
		{
			tmp = nbr;
			if (g_op->diese == 1 && g_op->zero == 1 && k != 0 &&
					(g_op->c == 'x' || g_op->c == 'X') && padd[0] == '0')
				nbr = pf_strjoin(pf_strjoin("0x", padd, 0), &(nbr[2]), 0);
			else
				nbr = pf_strjoin(padd, nbr, 0);
			free(tmp);
		}
	}
	return (nbr);
}

int			ft_putnbr_3(unsigned long long k)
{
	char	*nbr;
	int		i;

	i = 0;
	while (i < 4)
	{
		if (g_op->c == g_base[i].c)
			nbr = ft_reconvert(k, g_base[i].base);
		i++;
	}
	if (g_op->precision == 0 && g_op->dot == 1 && k == 0)
		nbr[0] = '\0';
	if (g_op->diese == 1 && g_op->c == 'o' && (k != 0 || nbr[0] == 0))
		nbr = pf_strjoin("0", nbr, 2);
	while (g_op->precision > (int)ft_strlen(nbr))
		nbr = pf_strjoin("0", nbr, 2);
	if (g_op->diese == 1 && k != 0 && (g_op->c == 'x' || g_op->c == 'X'))
		nbr = pf_strjoin("0x", nbr, 2);
	nbr = ft_padding_oux(nbr, k);
	if (g_op->c == 'X')
		nbr = ft_to_maj(nbr);
	ft_putstr_fd(nbr, g_op->fd);
	i = ft_strlen(nbr);
	free(nbr);
	return (i);
}

static char	*ft_padding_id(char *nbr)
{
	char	*padd;
	char	*tmp;

	padd = (g_op->zero == 1 && g_op->dot == 0 ? "0" : " ");
	if (nbr[0] != '-' && nbr[0] != '+' && g_op->space == 1)
		nbr = pf_strjoin(" ", nbr, 2);
	while (g_op->width > (int)ft_strlen(nbr))
	{
		if (g_op->moins == 1)
			nbr = pf_strjoin(nbr, " ", 1);
		else
		{
			tmp = nbr;
			if (nbr[0] == '+' && padd[0] == '0')
				nbr = pf_strjoin("+0", &(nbr[1]), 0);
			else if (nbr[0] == '-' && padd[0] == '0')
				nbr = pf_strjoin("-0", &(nbr[1]), 0);
			else if (nbr[0] == ' ' && g_op->space == 1)
				nbr = pf_strjoin(pf_strjoin(" ", padd, 0), &(nbr[1]), 0);
			else
				nbr = pf_strjoin(padd, nbr, 0);
			free(tmp);
		}
	}
	return (nbr);
}

int			ft_putnbr_2(long long k)
{
	char	*nbr;
	int		i;

	if (k == -9223372036854775802)
		nbr = ft_strdup("9223372036854775802");
	else
		nbr = (k < 0 ? ft_reconvert(-k, "0123456789") :
				ft_reconvert(k, "0123456789"));
	if (g_op->precision == 0 && g_op->dot == 1 && k == 0)
		nbr[0] = '\0';
	while (g_op->precision > (int)ft_strlen(nbr))
		nbr = pf_strjoin("0", nbr, 2);
	if (g_op->plus == 1 && k >= 0)
		nbr = pf_strjoin("+", nbr, 2);
	else if (k < 0)
		nbr = pf_strjoin("-", nbr, 2);
	nbr = ft_padding_id(nbr);
	ft_putstr_fd(nbr, g_op->fd);
	i = ft_strlen(nbr);
	free(nbr);
	return (i);
}
