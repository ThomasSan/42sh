/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 16:37:23 by tsanzey           #+#    #+#             */
/*   Updated: 2015/11/30 17:09:22 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	void	*dst;

	dst = (void*)malloc(sizeof(dst) * size);
	if (!dst)
		return (NULL);
	ft_memset(dst, 0, size);
	return (dst);
}
