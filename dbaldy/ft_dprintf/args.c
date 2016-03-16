/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 09:35:46 by dbaldy            #+#    #+#             */
/*   Updated: 2016/01/22 16:02:36 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int		nb_ch(long long nb)
{
	unsigned int		k;

	k = 0;
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		nb /= 10;
		k++;
	}
	return (k);
}

void				flags_1(char *str)
{
	int			i;

	i = 0;
	while (str[i + 1])
	{
		if (str[i] == '-')
			g_trait = ((g_trait & OPT_MIN) == 0) ? g_trait + OPT_MIN :
				g_trait;
		if (str[i] == '+')
			g_trait = ((g_trait & OPT_PLUS) == 0) ? g_trait + OPT_PLUS :
				g_trait;
		if (str[i] == '#')
			g_trait = ((g_trait & OPT_DIESE) == 0) ? g_trait + OPT_DIESE :
				g_trait;
		if (str[i] == '0' && i == 0)
			g_trait += OPT_ZERO;
		if (str[i + 1] == '0' && (str[i] > '9' || str[i] <= '0') &&
				str[i] != '.')
			g_trait = ((g_trait & OPT_ZERO) != OPT_ZERO) ? g_trait + OPT_ZERO :
				g_trait;
		if (str[i] == ' ')
			g_trait = ((g_trait & OPT_SPACE) != OPT_SPACE) ? g_trait +
				OPT_SPACE : g_trait;
		i++;
	}
}

void				flags_4(char *str)
{
	int			i;

	i = 0;
	while (str[i + 1])
	{
		if (str[i] == 'h')
		{
			if ((g_trait & OPT_H) != OPT_H)
				g_trait = (g_trait & OPT_HH) ? g_trait - OPT_HH + OPT_H :
					g_trait + OPT_H;
			else
				g_trait = ((g_trait & OPT_HH) == 0) ? g_trait + OPT_HH - OPT_H :
					g_trait - OPT_H;
		}
		else if (str[i] == 'l')
		{
			if ((g_trait & OPT_L) != OPT_L)
				g_trait = (g_trait & OPT_LL) ? g_trait - OPT_LL + OPT_L :
					g_trait + OPT_L;
			else
				g_trait = ((g_trait & OPT_LL) == 0) ? g_trait + OPT_LL - OPT_L :
					g_trait - OPT_L;
		}
		i++;
	}
}

void				flags_2(char *str)
{
	int			i;

	i = 0;
	while (str[i + 1])
	{
		if (str[i] == 'j' && (g_trait & OPT_J) != OPT_J)
			g_trait += OPT_J;
		else if (str[i] == 'z' && (g_trait & OPT_Z) != OPT_Z)
			g_trait += OPT_Z;
		i++;
	}
}

void				flags_3(char *str)
{
	int			i;

	i = 0;
	while (str[i + 1])
	{
		if (str[i] == '.')
		{
			g_precision = ft_atoi(&str[i + 1]);
			g_precision = (g_precision == 0) ? -1 : g_precision;
			i += nombre_digit(&str[i + 1]);
		}
		else if (str[i] > '0' && str[i] <= '9' && ((i == 0) ||
					(i > 0 && str[i - 1] != '.')))
		{
			g_width = ft_atoi(&str[i]);
			i += nombre_digit(&str[i]) - 1;
		}
		i++;
	}
}
