/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 15:27:53 by cbaldy            #+#    #+#             */
/*   Updated: 2016/04/27 18:23:35 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		ft_count_words(char const *s, char c)
{
	int		i;
	int		words;

	words = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			words++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		else
			i++;
	}
	return (words);
}

static int		ft_len_word(char const *s, char c)
{
	int		i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t	i[4];
	char	**str;

	i[3] = 0;
	if (s == NULL || (i[3] = ft_count_words(s, c)) == 0)
		return (NULL);
	if ((str = (char **)malloc(sizeof(char *) * (i[3] + 1))) == NULL)
		return (NULL);
	i[1] = 0;
	i[0] = 0;
	while (s[i[0]])
	{
		if (s[i[0]] == c)
			i[0]++;
		else if (s[i[0]] != '\0')
		{
			str[i[1]] = ft_strsub(s, i[0], ft_len_word(&s[i[0]], c));
			i[0] = i[0] + ft_len_word(&s[i[0]], c);
			i[1]++;
		}
	}
	str[i[1]] = NULL;
	return (str);
}
