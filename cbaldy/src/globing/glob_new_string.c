/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_new_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 17:45:18 by dbaldy            #+#    #+#             */
/*   Updated: 2016/04/25 14:29:35 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"

static char		*word_to_glob(char *str, int *i)
{
	int		le;

	le = *i;
	while (*i > 1 && str[*i - 1] != ' ' && str[*i - 1] != '/' &&
			str[*i - 1] != '\n')
		(*i)--;
	while (str[le] && str[le] != ' ' && str[le] != '/' && str[le] != '\n')
		le++;
	le = le - *i;
	return (ft_strsub(str, *i, le));
}

static char		*path_to_explore(char *str, int i)
{
	int		var;
	char	*tmp;
	char	*ret;

	var = 0;
	while (i > 1 && str[i - 1] != ' ' && str[i - 1] != '\n')
	{
		var++;
		i--;
	}
	tmp = ft_strsub(str, i, var);
	if (ft_strchr(tmp, '/') != NULL)
		ret = ft_strtrunc(tmp, '/');
	else
		ret = ft_strdup(".");
	free(tmp);
	tmp = (ft_strcmp(ret, "/") != 0) ? ft_strjoin(ret, "/") : ft_strdup(ret);
	free(ret);
	return (tmp);
}
/*
static t_glob_list 	*glob_progressiv(char *str, int i)
{
	char		*word;
	char		*path;
	t_glob_list	*match_list;

	path = path_to_explore(str, i);
	word = word_to_glob(str, &i);
	match_list = build_match_list(&path, word);
	return (match_list);
}
*/
static int			glob_maison(char **str, int i)
{
	t_glob_list	*match_list;
	char		*path;
	char		*word;

	if ((*str)[i] == '[' && ft_strchr(&((*str)[i + 1]), ']') == NULL)
		return (-1);
	path = path_to_explore(*str, i);
	word = word_to_glob(*str, &i);
	match_list = build_match_list(&path, word);
	if (match_list == NULL)
		return (-1);
	if (ft_strncmp(&((*str)[i]), "./", 2) != 0 && ft_strncmp(path, "./", 2) == 0)
	{
		word = ft_strsub(path, 2, ft_strlen(path) - 2);
		free(path);
		path = word;
	}
	glob_modif_str(str, match_list, i, path);
	clear_matchlist(match_list);
	ft_printf("str: %s\n", *str);
	return (0);
}

int				glob_new_string(char **str)
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
			if (glob_maison(str, i) < 0)
				return (-1);
			i = 0;
		}
		else if ((*str)[i] != '\0')
			i = ((*str)[i] == 0x5c) ? i + 2 : i + 1;
	}
	return (0);
}
