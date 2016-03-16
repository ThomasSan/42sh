/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conforme.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 13:52:27 by dbaldy            #+#    #+#             */
/*   Updated: 2016/01/30 15:16:35 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		g_opt[] = "-+#0 ";
char		g_larg[] = ".0123456789";
char		g_flags[] = "hljz";
char		g_conv[] = "sSpdDioOuUxXcC";
char		g_tot[] = "sSpdDioOuUxXcC#0-+ 0123456789.hljz";

char			analyse(char fm, const char *check)
{
	int			j;

	j = 0;
	while (check[j])
	{
		if (fm == check[j])
			return (check[j]);
		j++;
	}
	return (0);
}

int				conforme(const char *fm, int j)
{
	char	data;
	int		buf;

	buf = j;
	data = 0;
	j++;
	while (fm[j] && analyse(fm[j], g_tot) != 0 && data == 0)
	{
		data = analyse(fm[j], g_conv);
		j++;
	}
	if (data == 0 && fm[j] == '\0')
		return (-1);
	else if (data == 0)
		return (j + 1 - buf);
	return (j - buf);
}

void			treat_unconform(char c)
{
	int			i;
	char		*str;
	char		*padd;

	padd = (g_trait & OPT_ZERO) ? "0" : " ";
	if ((str = (char *)malloc(sizeof(char) * g_width)) == NULL)
		exit(1);
	str[0] = c;
	str[1] = '\0';
	i = 1;
	while (i < g_width)
	{
		if (g_trait & OPT_MIN)
			str = complete_behind(str, 2, " ");
		else
			str = complete(str, 1, padd);
		i++;
	}
	g_print += ft_strlen(str);
	ft_putstr_fd(str, g_fd);
	free(str);
}
