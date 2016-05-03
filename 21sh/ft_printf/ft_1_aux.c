/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_1_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 14:28:42 by cbaldy            #+#    #+#             */
/*   Updated: 2016/01/28 17:58:55 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*g_conv = "sSpdDioOuUxXcC%";
char		*g_valid = ". 0123456789#+-hljz";

int					ft_len_opt(char *opt)
{
	int		i;

	i = 1;
	while (opt[i] != '\0')
	{
		if (ft_strchr(g_conv, opt[i]) != NULL)
			return (i + 1);
		else if (ft_strchr(g_valid, opt[i]) == NULL)
			return (i + 1);
		i++;
	}
	return (i);
}

int					ft_nu_arg(char *str, int i)
{
	int		j;
	int		nu_arg;

	j = 0;
	nu_arg = 0;
	while (j < i && str[j] != '\0')
	{
		if (str[j] == '%')
		{
			j += ft_len_opt(&(str[j])) - 1;
			if (str[j] != '%' && ft_strchr(g_conv, str[j]) != NULL)
				nu_arg++;
		}
		j++;
	}
	return (nu_arg);
}

unsigned long long	ft_power_cv(unsigned long long nb, int power_cv)
{
	unsigned long long	i;

	if (power_cv < 0)
		return (0);
	else
	{
		i = 1;
		while (power_cv > 0)
		{
			i = nb * ft_power_cv(nb, power_cv - 1);
			power_cv = 0;
		}
		return (i);
	}
}

char				*ft_reconvert(unsigned long long nbr, char *base_to)
{
	unsigned long long	i[5];
	char				*ptr;

	i[1] = 1;
	i[0] = nbr;
	while (i[0] / ft_strlen(base_to) > 0)
	{
		i[1]++;
		i[0] = i[0] / ft_strlen(base_to);
	}
	ptr = (char *)malloc(sizeof(char) * i[1] + 1);
	i[1]--;
	ptr[0] = base_to[nbr / ft_power_cv(ft_strlen(base_to), i[1])];
	i[3] = 1;
	while (i[1] > 0)
	{
		i[4] = nbr / ft_power_cv(ft_strlen(base_to), i[1] - 1);
		ptr[i[3]] = base_to[i[4] % ft_strlen(base_to)];
		i[1]--;
		i[3]++;
	}
	ptr[i[3]] = '\0';
	return (ptr);
}

char				*ft_to_maj(char *nbr)
{
	int		i;

	i = 0;
	while (nbr[i] != '\0')
	{
		if (nbr[i] >= 'a' && nbr[i] <= 'z')
			nbr[i] = nbr[i] - 'a' + 'A';
		i++;
	}
	return (nbr);
}
