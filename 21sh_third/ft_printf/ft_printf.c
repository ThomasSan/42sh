/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 14:28:56 by cbaldy            #+#    #+#             */
/*   Updated: 2016/01/29 15:11:56 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_put			g_put_func[] = {
	{'d', &ft_idprint},
	{'i', &ft_idprint},
	{'s', &ft_sprint},
	{'S', &ft_sprint},
	{'o', &ft_ouxprint},
	{'x', &ft_ouxprint},
	{'X', &ft_ouxprint},
	{'u', &ft_ouxprint},
	{'D', &ft_douprint},
	{'O', &ft_douprint},
	{'U', &ft_douprint},
	{'%', &ft_percentprint},
	{'p', &ft_pprint},
	{'c', &ft_cprint},
	{'C', &ft_cprint},
};

static int		ft_valid(char *str, int i)
{
	char	*valid;
	char	*flag;
	int		j;

	flag = "sSpdDioOuUxXcC%";
	valid = ". 1234567890#+-hljz";
	j = 1;
	while (str[i + j] == '\0' || ft_strchr(flag, str[i + j]) == NULL)
	{
		if (str[i + j] == '\0' || ft_strchr(valid, str[i + j]) == NULL)
			return (-1);
		j++;
	}
	return (0);
}

static int		ft_imprime(char c, va_list ap2)
{
	int		z;

	z = 0;
	while (z < 15)
	{
		if (g_put_func[z].id == c)
			return (g_put_func[z].f(ap2));
		z++;
	}
	return (0);
}

int				ft_convert(char *str, va_list ap, int i, int fd)
{
	va_list		ap2;
	int			k;
	int			p;

	k = 0;
	if (ft_valid(str, i) == -1)
		return (ft_invalid_conv(str, i, fd));
	va_copy(ap2, ap);
	g_op = ft_read_option(str, i);
	g_op->fd = fd;
	while (k < ft_nu_arg(str, i))
	{
		va_arg(ap2, int);
		k++;
	}
	p = ft_imprime(str[i + ft_len_opt(&(str[i])) - 1], ap2);
	va_end(ap2);
	free(g_op);
	return (p);
}

int				ft_printf(char *str, ...)
{
	va_list ap;
	int		i;
	int		count;

	count = 0;
	i = 0;
	va_start(ap, str);
	while (str[i] != '\0')
	{
		if (str[i] != '%')
		{
			count++;
			write(1, &(str[i]), 1);
		}
		else
		{
			count += ft_convert(str, ap, i, 1);
			i += ft_len_opt(&(str[i])) - 1;
		}
		i++;
	}
	va_end(ap);
	return (count);
}
