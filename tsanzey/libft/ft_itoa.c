/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 18:18:20 by tsanzey           #+#    #+#             */
/*   Updated: 2015/11/26 14:37:40 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		size_len(int n)
{
	int		i;

	i = 0;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n > 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

static char		*itostr(int n, char *s, int len)
{
	if (n < 0)
	{
		n = -n;
		s[0] = '-';
	}
	while (n > 0)
	{
		s[len] = (n % 10) + '0';
		n = n / 10;
		len--;
	}
	return (s);
}

char			*ft_itoa(int n)
{
	char	*str;
	int		len;

	if (n == 0)
		return (str = "0");
	if (n == -2147483648)
		return (str = "-2147483648");
	len = size_len(n);
	str = (char *)malloc(sizeof(str) * len);
	if (!str)
		return (NULL);
	str[len] = '\0';
	len--;
	str = itostr(n, str, len);
	return (str);
}
