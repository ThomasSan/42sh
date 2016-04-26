/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/06 16:38:56 by cbaldy            #+#    #+#             */
/*   Updated: 2015/12/06 17:20:14 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			k;
	unsigned char	*dest1;
	unsigned char	*src1;
	unsigned char	c1;

	dest1 = (unsigned char *)dest;
	src1 = (unsigned char *)src;
	c1 = (unsigned char)c;
	k = 0;
	while (k < n)
	{
		(dest1)[k] = (src1)[k];
		if (src1[k] == c1)
			return ((void *)dest + k + 1);
		k++;
	}
	return (NULL);
}
