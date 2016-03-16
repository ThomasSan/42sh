/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 16:34:12 by dbaldy            #+#    #+#             */
/*   Updated: 2015/11/30 12:17:13 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const char			*str;
	const char			*dst;

	i = 0;
	dst = s1;
	str = s2;
	while (i < n)
	{
		if (str[i] != dst[i])
			return ((unsigned char)dst[i] - (unsigned char)str[i]);
		i++;
	}
	return (0);
}
