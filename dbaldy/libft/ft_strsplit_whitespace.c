/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_whitespace.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/14 17:51:24 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/14 18:00:08 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static int		escape_quotes(char const *s, unsigned int j)
{
	int		i;

	i = j;
	if (s[i] == '"')
	{
		i++;
		while (s[i] && s[i] != '"')
			i++;
	}
	if ((unsigned char)s[i] == 39)
	{
		i++;
		while (s[i] && (unsigned char)s[i] != 39)
			i++;
	}
	return (i - j);
}

static int		ft_count(char const *s)
{
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
	{
		i += escape_quotes(s, i);
		if (s[i] && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t') &&
	s[i + 1] != '\0' && s[i + 1] != ' ' && s[i + 1] != '\n' && s[i + 1] != '\t')
			j++;
		i++;
	}
	return (j + 1);
}

static int		ft_size(char const *s, unsigned int i)
{
	unsigned int	j;

	j = i;
	while (s[i])
	{
		i += escape_quotes(s, i);
		if (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
			break ;
		i++;
	}
	return ((i - j));
}

char			**ft_strsplit_whitespace(char const *s)
{
	char				**s1;
	unsigned int		i;
	unsigned int		j;
	int					size;

	if (s == NULL)
		return (NULL);
	if ((s1 = (char**)malloc((ft_count(s) + 1) * sizeof(char*))) == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s[j])
	{
		if (s[j] != ' ' && s[j] != '\n' && s[j] != '\t')
		{
			size = ft_size(s, j);
			s1[i] = ft_strsub(s, j, size);
			i++;
			j = size + j;
		}
		else
			j++;
	}
	s1[i] = NULL;
	return (s1);
}
