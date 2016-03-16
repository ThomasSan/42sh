/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_adv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 14:28:44 by dbaldy            #+#    #+#             */
/*   Updated: 2016/01/14 13:35:22 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>
#include <limits.h>

static int	ft_size(long long value, int base)
{
	int			size;

	size = 1;
	if (value < 0 && base == 10)
		size++;
	value = (value < 0) ? -value : value;
	while (value /= base)
		size++;
	return (size);
}

static char	*build(int size, long long value, char *base)
{
	int			i;
	char		*str;
	long long	n;

	i = 0;
	n = ft_strlen(base);
	if ((str = (char *)malloc(sizeof(char) * (size + 1))) == NULL)
		exit(1);
	if (value < 0 && n == 10)
	{
		str[0] = '-';
		i = 1;
	}
	value = (value < 0) ? -value : value;
	str[size] = '\0';
	while (size-- > i)
	{
		str[size] = base[value % n];
		value /= n;
	}
	return (str);
}

char		*ft_itoa_adv(long long value, char *base)
{
	char	*str;

	if (value == LLONG_MIN && ft_strlen(base) == 10)
	{
		str = ft_strdup("-9223372036854775808");
		return (str);
	}
	str = build(ft_size(value, ft_strlen(base)), value, base);
	return (str);
}
