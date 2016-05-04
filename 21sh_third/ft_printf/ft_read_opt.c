/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_opt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 14:20:04 by cbaldy            #+#    #+#             */
/*   Updated: 2016/01/29 14:08:50 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*g_flag = "0+-# ";

static t_op	*ft_init_op(char *str, int i)
{
	t_op	*op;

	if ((op = (t_op *)malloc(sizeof(t_op))) == NULL)
		return (NULL);
	g_op = NULL;
	op->size = 0;
	op->precision = 0;
	op->width = 0;
	op->diese = 0;
	op->zero = 0;
	op->moins = 0;
	op->space = 0;
	op->plus = 0;
	op->dol = 0;
	op->dot = 0;
	op->fd = 1;
	op->c = str[ft_len_opt(&(str[i])) + i - 1];
	return (op);
}

static int	ft_read_size(char *s, t_op *op)
{
	if (s[0] == 'h' && op->size < 2)
		op->size = 2;
	else if (s[0] == 'h' && op->size == 2)
		op->size = 1;
	else if (s[0] == 'z' && op->size < 3)
		op->size = 3;
	else if (s[0] == 'l' && (op->size < 4 || op->size == 5))
		op->size = 4;
	else if (s[0] == 'l' && op->size == 4)
		op->size = 5;
	else if (s[0] == 'j' && op->size < 6)
		op->size = 6;
	return (1);
}

static int	ft_read_nu(char *str, t_op *op)
{
	int		k;
	int		nb;

	k = 0;
	nb = ft_atoi(str);
	while (str[k] >= '0' && str[k] <= '9')
		k++;
	if (str[k] == '$')
		op->dol = nb;
	else
		op->width = nb;
	return (k);
}

static int	ft_read_flag(char c, t_op *op)
{
	if (c == '0')
		op->zero = 1;
	else if (c == '#')
		op->diese = 1;
	else if (c == '+')
		op->plus = 1;
	else if (c == '-')
		op->moins = 1;
	else if (c == ' ')
		op->space = 1;
	return (1);
}

t_op		*ft_read_option(char *str, int i)
{
	t_op	*op;
	int		k;

	op = ft_init_op(str, i);
	k = i + ft_len_opt(&(str[i]));
	while (i < k && str[i] != '\0')
	{
		if (str[i] == 'h' || str[i] == 'l' || str[i] == 'z' || str[i] == 'j')
			i += ft_read_size(&(str[i]), op);
		else if (str[i] == '.')
		{
			op->dot = 1;
			i++;
			op->precision = ft_read_precision(&(str[i]));
			while (str[i] >= '0' && str[i] <= '9')
				i++;
		}
		else if (str[i] > '0' && str[i] <= '9')
			i += ft_read_nu(&(str[i]), op);
		else if (ft_strchr(g_flag, str[i]) != NULL)
			i += ft_read_flag(str[i], op);
		else
			i++;
	}
	return (op);
}
