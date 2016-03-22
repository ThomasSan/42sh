/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 11:44:37 by tsanzey           #+#    #+#             */
/*   Updated: 2015/11/24 16:36:08 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t len)
{
	unsigned int	i;
	char			*tmp;

	i = 0;
	tmp = (char*)str;
	while (i < len)
	{
		tmp[i] = c;
		i++;
	}
	return (tmp);
}
