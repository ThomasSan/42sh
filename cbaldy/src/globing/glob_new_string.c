/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_new_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 17:45:18 by dbaldy            #+#    #+#             */
/*   Updated: 2016/04/27 11:10:00 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"

static char			*word_to_glob(char *str, int i)
{
	int j;

	j = i;
	while (i > 1 && str[i - 1] != ' ' && str[i - 1] != '\n')
		i--;
	while (str[j] && str[j] != ' ' && str[j] != '\n')
		j++;
	return (ft_strsub(str, i, j - i));
}

static int			glob_maison(char **str, int *j)
{
	t_glob_list	*match_list;
	char		*word;
	int			i;

	i = *j;
	if ((*str)[i] == '[' && ft_strchr(&((*str)[i + 1]), ']') == NULL)
		return (-1);
	word = word_to_glob(*str, i);
	match_list = glob_progressiv(word);
	if (match_list == NULL)
	{
		free(word);
		return (-1);
	}
	glob_modif_str(str, match_list, word, j);
	clear_matchlist(match_list);
	free(word);
	return (0);
}

static int			glob_new_string(char **str)
{
	int			i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == ' ' && (*str)[i + 1] == '~')
			alias_ihome(str, i + 1);
		else if ((*str)[i] == 0x22 || (*str)[i] == 0x27)
			escape_quotes(*str, &i, (*str)[i]);
		else if ((*str)[i] == '$')
			replace_dollar(str, &i);
		else if ((*str)[i] == '*' || (*str)[i] == '?' || (*str)[i] == '[')
		{
			if (glob_maison(str, &i) < 0)
				return (-1);

		}
		else if ((*str)[i] != '\0')
			i = ((*str)[i] == 0x5c) ? i + 2 : i + 1;
	}
	return (0);
}

int					glob_it(char **glob, char *str)
{
	if (glob_new_string(glob) == -1)
	{
		free(*glob);
		ft_dprintf(STDERR_FILENO, "sh: no matches found: %s\n", str);
		return (1);
	}
	if (ft_strlen(*glob) > 16384)
	{
		free(*glob);
		ft_dprintf(STDERR_FILENO, "sh: argument list too long: %s\n", str);
		return (1);
	}
	return (0);
}
