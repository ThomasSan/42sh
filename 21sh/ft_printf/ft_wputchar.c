/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wputchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 16:19:56 by cbaldy            #+#    #+#             */
/*   Updated: 2016/01/29 14:00:13 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		g_dec[] = "0123456789";
char		g_bi[] = "01";

static int	ft_size(char **nbr)
{
	int		max[6];
	int		i;

	max[0] = 7;
	max[1] = 11;
	max[2] = 16;
	max[3] = 21;
	max[4] = 26;
	max[5] = 31;
	i = 0;
	while (i < 6)
	{
		if ((int)ft_strlen(*nbr) <= max[i])
		{
			while ((int)ft_strlen(*nbr) < max[i])
				*nbr = pf_strjoin("0", *nbr, 2);
			return (i + 1);
		}
		i++;
	}
	return (-1);
}

static int	ft_cnf(char *str, char *base_from, char *base_to)
{
	char	*tmp;
	int		i;

	tmp = ft_convert_base(str, base_from, base_to);
	free(str);
	i = ft_atoi(tmp);
	free(tmp);
	return (i);
}

static int	ft_wputchar(char *nbr, int size)
{
	int				i[2];
	unsigned char	*bytes;

	if ((bytes = (unsigned char *)malloc(sizeof(char) * size)) == NULL)
		return (0);
	i[0] = -1;
	while (i[0]++ < size - 1)
		bytes[i[0]] = ft_cnf(pf_strsub(nbr, i[0] * 8, 8, 0), g_bi, g_dec);
	i[1] = size;
	while ((g_op->c == 67 || g_op->c == 99) && g_op->width > i[1]
			&& g_op->moins == 0)
	{
		write(g_op->fd, (g_op->zero == 1 ? "0" : " "), 1);
		i[1]++;
	}
	write(g_op->fd, &(bytes[0]), size);
	while ((g_op->c == 'C' || g_op->c == 'c') && g_op->width > i[1])
	{
		write(g_op->fd, " ", 1);
		i[1]++;
	}
	free(nbr);
	free(bytes);
	return (i[1]);
}

static char	*ft_clean(int nb)
{
	char	*tmp;
	char	*buf;

	tmp = ft_reconvert(nb, g_dec);
	buf = ft_convert_base(tmp, g_dec, g_bi);
	free(tmp);
	return (buf);
}

int			ft_conv_wchar(int nb)
{
	int			i[3];
	char		*nbr[2];

	nbr[0] = ft_clean(nb);
	i[1] = ft_size(&nbr[0]);
	i[2] = 0;
	i[0] = 0;
	if ((nbr[1] = (char *)malloc(sizeof(char) * i[1] * 8 + 1)) == NULL)
		return (0);
	while (i[2] < (i[1] * 8))
	{
		if ((i[2] <= i[1] && i[1] > 1) || (i[2] < i[1]))
			nbr[1][i[2]] = (i[2] == i[1] || i[1] == 1 ? '0' : '1');
		else if (i[2] % 8 == 0 || (i[2] % 8 == 1 && i[2] != 1))
			nbr[1][i[2]] = (i[2] % 8 == 0 ? '1' : '0');
		else if (nbr[0] != '\0')
		{
			nbr[1][i[2]] = nbr[0][i[0]];
			i[0]++;
		}
		i[2]++;
	}
	nbr[1][(i[1] * 8)] = '\0';
	free(nbr[0]);
	return (ft_wputchar(nbr[1], i[1]));
}
