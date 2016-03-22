/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 12:16:19 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/22 13:01:39 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		k;

	k = 0;
	while (s[k])
		k++;
	while (k >= 0)
	{
		if (s[k] == c)
			return (&((char *)s)[k]);
		k--;
	}
	if (c == 0)
		return (&((char *)s)[k]);
	else
		return (NULL);
}
