/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 10:54:49 by dbaldy            #+#    #+#             */
/*   Updated: 2015/11/30 12:16:59 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c,
		size_t n)
{
	size_t					i;
	unsigned char			*str;
	const unsigned char		*source;
	unsigned char			g;

	i = 0;
	str = dst;
	source = src;
	g = (unsigned char)c;
	while (i < n)
	{
		str[i] = source[i];
		if (source[i] == g)
			return (&dst[i + 1]);
		i++;
	}
	str[i] = '\0';
	return (NULL);
}
