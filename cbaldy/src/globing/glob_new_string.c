/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_new_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 17:45:18 by dbaldy            #+#    #+#             */
/*   Updated: 2016/04/23 13:26:25 by dbaldy           ###   ########.fr       */
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
	tmp = ft_strjoin(ret, "/");
	free(ret);
	return (tmp);
}

int				glob_new_string(char **str)
{
	int			i;
	t_glob_list	*match_list;
	char		*word;
	char		*path;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '*' || (*str)[i] == '?' || (*str)[i] == '[')
		{
			if ((*str)[i] == '[' && ft_strchr(&((*str)[i + 1]), ']') == NULL)
				return (-1);
			path = path_to_explore(*str, i);
			word = word_to_glob(*str, &i);
			match_list = build_match_list(&path, word);
			free(word);
			if (match_list == NULL)
				return (-1);
			glob_modif_str(str, match_list, i, path);
			clear_matchlist(match_list);
		}
		i++;
	}
	return (0);
}
