/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 12:25:45 by cbaldy            #+#    #+#             */
/*   Updated: 2015/11/29 18:15:48 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	int			i[3];

	i[0] = 0;
	if (s2[0] == '\0')
		return ((char *)s1);
	while (s1[i[0]] != '\0')
	{
		i[2] = 0;
		i[1] = 0;
		while (s2[i[1]] != '\0')
		{
			if (s1[i[0] + i[1]] == s2[i[1]])
				i[2]++;
			i[1]++;
		}
		if (i[2] == i[1])
			return (&((char *)s1)[i[0]]);
		i[0]++;
	}
	return (NULL);
}
