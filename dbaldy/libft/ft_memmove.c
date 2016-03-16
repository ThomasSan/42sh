/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 11:49:53 by dbaldy            #+#    #+#             */
/*   Updated: 2015/11/30 12:17:41 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dest;
	char		*source;
	size_t		i;

	i = 0;
	dest = dst;
	source = (char*)malloc(len);
	ft_memcpy(source, src, len);
	while (i < len)
	{
		dest[i] = source[i];
		i++;
	}
	return (dst);
}
