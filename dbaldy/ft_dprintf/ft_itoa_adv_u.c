/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_adv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 14:28:44 by dbaldy            #+#    #+#             */
/*   Updated: 2016/01/14 13:35:30 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>
#include <stdio.h>

static int	ft_size(unsigned long long value, int base)
{
	int			size;

	size = 1;
	while (value /= base)
		size++;
	return (size);
}

static char	*build(int size, unsigned long long value, char *base)
{
	int			i;
	char		*str;
	int			n;

	i = 0;
	n = ft_strlen(base);
	if ((str = (char *)malloc(sizeof(char) * (size + 1))) == NULL)
		exit(1);
	str[size] = '\0';
	while (size-- > i)
	{
		str[size] = base[value % n];
		value /= n;
	}
	return (str);
}

char		*ft_itoa_adv_u(unsigned long long value, char *base)
{
	char	*str;

	str = build(ft_size(value, ft_strlen(base)), value, base);
	return (str);
}
