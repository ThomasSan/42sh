/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 11:14:03 by cbaldy            #+#    #+#             */
/*   Updated: 2015/11/25 11:52:37 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i[3];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	while (dest[i[0]] != '\0')
		i[0]++;
	while (src[i[1]] != '\0')
		i[1]++;
	while (src[i[2]] != '\0' && i[2] + i[0] < size - 1 && size > 0)
	{
		dest[i[0] + i[2]] = src[i[2]];
		i[2]++;
	}
	if (i[0] + i[2] > size)
		return (i[1] + size);
	else
	{
		dest[i[0] + i[2]] = '\0';
		return (i[0] + i[1]);
	}
}
