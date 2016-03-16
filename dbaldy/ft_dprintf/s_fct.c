/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_fct.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 09:09:56 by dbaldy            #+#    #+#             */
/*   Updated: 2016/02/08 16:39:04 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*fill_str(void)
{
	char		*str;
	int			i;

	i = 0;
	if ((str = (char*)malloc(sizeof(char) * (g_width + 1))) == NULL)
		exit(1);
	while (i < g_width)
	{
		str[i] = '0';
		i++;
	}
	str[i] = '\0';
	return (str);
}

char		*format_s(char *str)
{
	char	*tmp;
	char	*padd;

	padd = (g_trait & OPT_ZERO) ? "0" : " ";
	if (g_precision < 0)
	{
		free(str);
		str = ft_strdup("");
	}
	if (g_precision > 0)
	{
		tmp = ft_strsub(str, 0, g_precision);
		free(str);
		str = tmp;
	}
	while (ft_strlen(str) < g_width)
	{
		if (g_trait & OPT_MIN)
			str = complete_behind(str, 2, " ");
		else
			str = complete(str, 1, padd);
	}
	return (str);
}

char		*get_winch2(char *str, char *tmp)
{
	char	*buf;

	buf = ft_strdup(str);
	free(str);
	str = ft_strjoin(buf, tmp);
	free(buf);
	free(tmp);
	return (str);
}

void		get_winch(va_list ap)
{
	wchar_t		*res;
	int			i;
	char		*str;
	char		*tmp;

	i = 0;
	str = ft_strdup("");
	res = va_arg(ap, wchar_t*);
	if (res == NULL)
		str = ft_strdup("(null)");
	else
	{
		while (res[i])
		{
			tmp = treatwint(res[i]);
			if (g_precision > 0 && ft_strlen(str) + ft_strlen(tmp) >
					g_precision)
				break ;
			str = get_winch2(str, tmp);
			i++;
		}
		str = format_s(str);
	}
	check_print(str);
}

void		check_print(char *str)
{
	g_print += ft_strlen(str);
	write(g_fd, str, ft_strlen(str));
	if (ft_strcmp("", str) != 0)
		free(str);
}
