/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 18:57:43 by tsanzey           #+#    #+#             */
/*   Updated: 2015/11/26 19:01:50 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *sub, size_t n)
{
	unsigned int	i;
	int				j;

	i = 0;
	if (*sub == '\0')
		return ((char *)str);
	while (str[i] && i < n)
	{
		j = 0;
		while (str[i + j] == sub[j] && sub[j] && i + j < n)
			j++;
		if (!sub[j])
			return ((char *)str + i);
		i++;
	}
	return (NULL);
}
