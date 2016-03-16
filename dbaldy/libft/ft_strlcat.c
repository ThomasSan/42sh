/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 11:02:59 by dbaldy            #+#    #+#             */
/*   Updated: 2015/11/30 12:20:18 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = ft_strlen(dst);
	if (size == 0)
		return (j);
	while (src[i] != '\0' && j + i < size - 1)
	{
		dst[j + i] = src[i];
		i++;
	}
	if (size < i + j)
		return (ft_strlen(src) + size);
	else
	{
		dst[i + j] = '\0';
		return (j + ft_strlen(src));
	}
}
