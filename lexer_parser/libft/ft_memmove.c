/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:14:24 by tsanzey           #+#    #+#             */
/*   Updated: 2015/11/26 14:53:33 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*res;

	res = (unsigned char*)malloc(sizeof(*res) * len);
	ft_memcpy(res, src, len);
	ft_memcpy(dst, res, len);
	free(res);
	return (dst);
}
