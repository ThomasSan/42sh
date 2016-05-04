/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 12:10:13 by cbaldy            #+#    #+#             */
/*   Updated: 2015/11/30 19:17:21 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		k;
	char		*cpy;
	char		*source;

	cpy = (char *)dest;
	source = (char *)malloc(n);
	source = ft_memcpy(source, src, n);
	k = 0;
	while (k < n)
	{
		cpy[k] = source[k];
		k++;
	}
	return (dest);
}
