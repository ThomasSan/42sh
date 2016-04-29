/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_match.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 19:54:00 by dbaldy            #+#    #+#             */
/*   Updated: 2016/04/29 11:19:31 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"

static int	skip_to_glob(char *buf, char *tested, char *word)
{
	if ((word + 1 - buf) == 0)
	{
		if (*buf == '\0')
			return (1);
		else
			while (*tested && match(tested, word + 1) == 0)
				tested++;
		if (*tested != '\0')
			return (1);
		return (-1);
	}
	return (0);
}

static int	test_bracket(char *tested, char *word)
{
	char	*one_carac;
	char	*buf;
	char	*after_brack;

	word++;
	if (ft_strchr(word, ']') == NULL)
		return (0);
	one_carac = ft_strnew(2);
	ft_bzero(one_carac, 2);
	after_brack = ft_strchr(word, ']') + 1;
	while (*word != ']')
	{
		one_carac = ft_strncpy(one_carac, word, 1);
		buf = ft_strjoin(one_carac, after_brack);
		if (match(tested, buf) == 1)
		{
			free(buf);
			free(one_carac);
			return (1);
		}
		free(buf);
		word++;
	}
	free(one_carac);
	return (0);
}

static int	question_mark(char *tested, char *word)
{
	if (*tested == '\0')
		return (0);
	if (*(word + 1) == '\0' && *(tested + 1) != '\0')
		return (0);
	return (match(tested + 1, word + 1));
}

static int	star(char *tested, char *word)
{
	char	*buf;
	char	*ret;
	int		skip;

	buf = word + 1;
	while (*buf && *buf != '*' && *buf != '?' && *buf != '[')
		buf++;
	if ((skip = skip_to_glob(buf, tested, word)) == 1)
		return (1);
	else if (skip == -1)
		return (0);
	buf = ft_strsub(word + 1, 0, buf - (word + 1));
	ret = ft_strstr(tested, buf);
	while (ret != NULL &&
			(match(ret + ft_strlen(buf), word + ft_strlen(buf) + 1)) == 0)
		ret = ft_strstr(ret + ft_strlen(buf), buf);
	free(buf);
	if (ret == NULL)
		return (0);
	return (1);
}

int			match(char *tested, char *word)
{
	if (*word == '\0' && *tested == '\0')
		return (1);
	if (*word == 0x5c)
		return (match(tested, word + 1));
	else if (*word == '*' || *word == '?' || *word == '[')
	{
		if (*word == '*')
			return (star(tested, word));
		else if (*word == '?')
			return (question_mark(tested, word));
		else if (*word == '[')
			return (test_bracket(tested, word));
	}
	else if (*word == *tested)
		return (match(tested + 1, word + 1));
	else
		return (0);
	return (1);
}
