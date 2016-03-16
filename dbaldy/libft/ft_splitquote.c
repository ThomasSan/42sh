/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 15:08:13 by dbaldy            #+#    #+#             */
/*   Updated: 2016/02/14 18:44:38 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		ft_count(char const *s, char c)
{
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if ((int)s[i] == (int)'"')
		{
			i++;
			while (s[i] && s[i] != '"')
				i++;
		}
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			j++;
		i++;
	}
	return (j + 1);
}

static int		ft_size(char const *s, char c)
{
	int		j;

	j = 0;
	while (s[j])
	{
		if (s[j] == '"')
		{
			j++;
			while (s[j] && s[j] != '"')
				j++;
		}
		if (s[j] == c)
			break ;
		j++;
	}
	return (j);
}

char			**ft_splitquote(char const *s, char c)
{
	char				**s1;
	unsigned int		i;
	unsigned int		j;

	s1 = (char**)malloc((ft_count(s, c) + 1) * sizeof(char*));
	if (s1 == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s[j])
	{
		if (s[j] != c)
		{
			s1[i] = ft_strsub(s, j, ft_size(&s[j], c));
			i++;
			j = ft_size(&s[j], c) + j;
		}
		else
			j++;
	}
	s1[i] = NULL;
	return (s1);
}
