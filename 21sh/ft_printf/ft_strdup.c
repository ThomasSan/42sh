/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 16:55:14 by cbaldy            #+#    #+#             */
/*   Updated: 2016/01/28 18:13:00 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char			*dest;
	unsigned long	f;
	unsigned long	k;

	f = ft_strlen(s1);
	if ((dest = (char *)malloc(f + 1)) == NULL)
		return (NULL);
	k = 0;
	while (k < f + 1)
	{
		dest[k] = s1[k];
		k++;
	}
	return (dest);
}
