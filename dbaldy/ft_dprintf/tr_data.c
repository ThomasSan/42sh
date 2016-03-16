/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impression1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 12:36:01 by dbaldy            #+#    #+#             */
/*   Updated: 2016/01/22 16:02:24 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_ptr	g_tbl_fct[] =
{
	{'s', &ft_puts},
	{'i', &ft_putint},
	{'d', &ft_putint},
	{'c', &ft_putc},
	{'x', &ft_putx},
	{'X', &ft_putmajx},
	{'o', &ft_putloo},
	{'p', &ft_putp},
	{'u', &ft_putu},
	{'b', &ft_putb},
	{'k', &ft_putk},
	{'D', &ft_putint},
	{'U', &ft_putu},
	{'O', &ft_putloo},
	{'C', &ft_putc},
	{'S', &ft_puts}
};

void			alias(char *str)
{
	if ((str[ft_strlen(str) - 1] == 'D') || (str[ft_strlen(str) - 1] == 'O') ||
	(str[ft_strlen(str) - 1] == 'U') || (str[ft_strlen(str) - 1] == 'S') ||
	(str[ft_strlen(str) - 1] == 'C'))
		g_trait += OPT_L;
}

void			analyse_flags(char *str)
{
	int			i;

	i = 0;
	g_width = 0;
	flags_1(str);
	flags_2(str);
	flags_4(str);
	flags_3(str);
	if ((str[ft_strlen(str) - 1] == 'd' || str[ft_strlen(str) - 1] == 'o' ||
	str[ft_strlen(str) - 1] == 'u' || str[ft_strlen(str) - 1] == 'x' ||
	str[ft_strlen(str) - 1] == 'X' || str[ft_strlen(str) - 1] == 'i' ||
	str[ft_strlen(str) - 1] == 'D' || str[ft_strlen(str) - 1] == 'O' ||
	str[ft_strlen(str) - 1] == 'p' || str[ft_strlen(str) - 1] == 'U')
			&& g_trait & OPT_ZERO && g_precision != 0)
		g_trait -= OPT_ZERO;
}

void			convert_data(va_list ap, char *str)
{
	int			i;

	i = 0;
	while (str[ft_strlen(str) - 1] != g_tbl_fct[i].c && i < 16)
		i++;
	if (i != 16)
		g_tbl_fct[i].f(ap);
	if (i == 16)
		treat_unconform(str[ft_strlen(str) - 1]);
}

int				tr_data(va_list ap, const char *fm, int j)
{
	int		i;
	char	*str;

	if (fm[j + 1] == '\0')
		return (1);
	g_trait = 0;
	g_precision = 0;
	if ((i = conforme(fm, j)) == -1)
		return (-1);
	str = ft_strsub(fm, (unsigned int)(j + 1), (unsigned int)(i - 1));
	alias(str);
	analyse_flags(str);
	convert_data(ap, str);
	free(str);
	return (i);
}
