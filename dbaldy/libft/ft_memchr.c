/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 16:06:37 by dbaldy            #+#    #+#             */
/*   Updated: 2015/11/30 12:17:07 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	ch;
	unsigned char	*str;

	str = (unsigned char*)s;
	ch = (unsigned char)c;
	i = 0;
	while (n--)
	{
		if (str[i] == ch)
			return ((void*)str + i);
		i++;
	}
	return (NULL);
}
