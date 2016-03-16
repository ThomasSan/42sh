/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 17:04:05 by dbaldy            #+#    #+#             */
/*   Updated: 2016/01/14 13:35:42 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*s2;
	size_t	k;

	i = 0;
	k = ft_strlen(s1);
	s2 = (char *)malloc(k + 1);
	if (s2 == NULL)
		return (NULL);
	while (i < k + 1)
	{
		s2[i] = s1[i];
		i++;
	}
	return (s2);
}
