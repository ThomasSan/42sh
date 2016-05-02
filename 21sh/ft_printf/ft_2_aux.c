/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/16 10:57:06 by cbaldy            #+#    #+#             */
/*   Updated: 2016/01/29 14:07:33 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_nb_bytes(wchar_t *s, int all)
{
	int		nb;
	int		i;
	int		flag;

	nb = 0;
	i = 0;
	flag = 0;
	while (s[i] != 0 && all != flag)
	{
		if (s[i] < 128)
			nb += 1;
		else if (s[i] < 2048)
			nb += 2;
		else if (s[i] < 65536)
			nb += 3;
		else if (s[i] < 2097152)
			nb += 4;
		else if (s[i] < 67108864)
			nb += 5;
		else
			nb += 6;
		i++;
		flag = 1;
	}
	return (nb);
}

int		ft_nb_printed_bytes(wchar_t *s)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (g_op->dot == 0)
		return (ft_nb_bytes(s, 2));
	while (count + ft_nb_bytes(&(s[i]), 1) <= g_op->precision)
	{
		count += ft_nb_bytes(&(s[i]), 1);
		i++;
	}
	return (count);
}

int		ft_read_precision(char *str)
{
	if (str[0] < '0' || str[0] > '9')
		return (0);
	else
		return (ft_atoi(str));
}

char	*pf_strjoin(char *s1, char *s2, int fr)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	if (fr == 1)
		free(s1);
	else if (fr == 2)
		free(s2);
	return (tmp);
}

char	*pf_strsub(char *s, unsigned int start, size_t len, int fr)
{
	char	*tmp;

	tmp = ft_strsub(s, start, len);
	if (fr == 1)
		free(s);
	return (tmp);
}
