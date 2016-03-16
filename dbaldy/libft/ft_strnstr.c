/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 16:07:43 by dbaldy            #+#    #+#             */
/*   Updated: 2015/11/30 12:20:55 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i[2];
	size_t	j;

	i[0] = 0;
	i[1] = 0;
	if (s2[0] == '\0')
		return ((char*)s1);
	while (s1[i[0]] && i[0] < n)
	{
		j = 0;
		if (s1[i[0]] == s2[j])
		{
			i[1] = i[0];
			while (s1[i[0]] == s2[j] && i[0] < n && s1[i[0]])
			{
				j++;
				i[0]++;
			}
			if (j == ft_strlen(s2))
				return ((char *)&s1[i[1]]);
			i[0] = i[1] + 1;
		}
		i[0]++;
	}
	return (NULL);
}
