/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 13:59:32 by tsanzey           #+#    #+#             */
/*   Updated: 2015/11/27 17:32:31 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned int	i;
	char			*d;
	const char		*s;

	i = 0;
	d = (char*)dst;
	s = (const char*)src;
	while (i < n && s[i] != (char)c)
	{
		d[i] = s[i];
		i++;
	}
	if (i == n)
		return (NULL);
	if (s[i] == (char)c)
	{
		d[i] = s[i];
		i++;
	}
	return (dst + i);
}
