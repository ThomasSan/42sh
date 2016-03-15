/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 18:15:21 by tsanzey           #+#    #+#             */
/*   Updated: 2015/11/26 14:48:39 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *to_find)
{
	int	j;
	int	i;

	i = 0;
	if (*to_find == '\0')
		return ((char*)str);
	while (str[i])
	{
		j = 0;
		if (str[i] == to_find[j])
			while (str[i + j] == to_find[j] && to_find[j])
				j++;
		if (!to_find[j])
			return ((char*)str + i);
		i++;
	}
	return (NULL);
}
