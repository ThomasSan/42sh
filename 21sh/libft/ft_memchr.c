/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:40:02 by cbaldy            #+#    #+#             */
/*   Updated: 2015/11/29 16:33:49 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *src, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	car;

	car = (unsigned char)c;
	str = (unsigned char *)src;
	while (n > 0)
	{
		if (*str == car)
			return ((void *)(str));
		str++;
		n--;
	}
	return (NULL);
}
