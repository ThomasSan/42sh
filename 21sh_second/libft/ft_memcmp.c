/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 15:33:50 by cbaldy            #+#    #+#             */
/*   Updated: 2015/11/27 18:36:23 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			k;
	unsigned char	*ss1;
	unsigned char	*ss2;

	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	k = 0;
	while (k < n)
	{
		if (ss1[k] != ss2[k])
			return ((unsigned int)ss1[k] - (unsigned int)ss2[k]);
		k++;
	}
	return (0);
}
