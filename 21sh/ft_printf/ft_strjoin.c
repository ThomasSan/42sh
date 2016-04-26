/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 14:42:50 by cbaldy            #+#    #+#             */
/*   Updated: 2016/01/28 18:11:46 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i[2];

	if ((str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1)) == NULL)
		return (NULL);
	i[0] = 0;
	i[1] = 0;
	while (s1[i[0]])
	{
		str[i[0]] = s1[i[0]];
		i[0]++;
	}
	while (s2[i[1]])
	{
		str[i[0] + i[1]] = s2[i[1]];
		i[1]++;
	}
	str[i[0] + i[1]] = '\0';
	return (str);
}
