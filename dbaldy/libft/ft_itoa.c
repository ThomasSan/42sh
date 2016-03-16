/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 12:37:49 by dbaldy            #+#    #+#             */
/*   Updated: 2015/11/30 12:14:54 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	*str;
	int		negative;
	int		size;
	int		buf;

	negative = (n < 0);
	size = 1;
	buf = n;
	while (buf /= 10)
		size++;
	str = ft_strnew(size + negative);
	if (str == NULL)
		return (NULL);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	str[0] = '-';
	n = (negative) ? -n : n;
	str[size + negative] = '\0';
	while (size--)
	{
		str[size + negative] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}
