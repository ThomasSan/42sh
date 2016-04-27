/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_modif_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 18:48:50 by dbaldy            #+#    #+#             */
/*   Updated: 2016/04/27 11:45:34 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"

static char		*get_replacement(char *var)
{
	char	*res;
	int 	i;

	i = 0;
	while (var[i])
	{
		var[i] = ft_toupper(var[i]);
		i++;
	}
	if ((i = sh_is_new_var(var)) >= 0)
		res = ft_strdup(ft_strchr(g_env[i], '=') + 1);
	else
		res = ft_strdup("");
	return (res);		
}

int				replace_dollar(char **str, int *i)
{
	int			j;
	char		*value;
	char		*var;
	char		*tmp;

	j = *i;
	if ((*str)[*i + 1] == '?')
	{
		*i += 2;
		return (0);
	}
	while ((*str)[j + 1] && (*str)[j + 1] != ' ' && (*str)[j + 1] != '\n'
			&& (*str)[j + 1] != '/')
		j++;
	var = ft_strsub(*str, *i + 1, j - *i);
	value = get_replacement(var);
	tmp = var;
	var = ft_strjoin("$", tmp);
	free(tmp);
	*str = ft_replace_str(*str, var, value);
	*i = (ft_strlen(value) == 0) ? *i + 1 : ft_strlen(value);
	free(var);
	free(value);
	return (0);
}

static int		add_bckslsh(char **to_add)
{
	int		i;
	char	*tmp;
	char	*begin;
	char	*end;

	i = 0;
	while ((*to_add)[i])
	{
		if ((*to_add)[i] == ' ')
		{
			begin = ft_strsub(*to_add, 0, i);
			end = ft_strdup(&((*to_add)[i]));
			tmp = ft_strjoin_multiple(3, begin, "\x5c", end);
			free(begin);
			free(end);
			free(*to_add);
			*to_add = tmp;		
			i += 1;
		}
		i++;
	}
	return (0);
}

static char		*full_glob(t_glob_list *match_list, char *word)
{
	char		*tmp;
	t_glob_list *l_buf;
	char		*insert;
	char		*to_add;

	l_buf = match_list;
	insert = ft_strdup("");
	while (l_buf)
	{
		tmp = ft_strdup(insert);
		free(insert);
		if (ft_strncmp(word, "./", 2) && ft_strncmp(l_buf->var, "./", 2) == 0)
			to_add = ft_strsub(l_buf->var, 2, ft_strlen(l_buf->var) - 2);
		else
			to_add = ft_strdup(l_buf->var);
		if (ft_strchr(to_add, ' ') != NULL)
			add_bckslsh(&to_add);
		insert = (ft_strcmp(tmp, "") == 0) ? ft_strdup(to_add) :
			ft_strjoin_multiple(3, tmp, " ", to_add);
		free(to_add);
		free(tmp);
		l_buf = l_buf->next;
	}
	return (insert);
}

int				glob_modif_str(char **str, t_glob_list *match_list, char *word
		, int *i)
{
	char		*insert;
	char		*tmp;

	insert = full_glob(match_list, word);
	tmp = ft_replace_str(*str, word, insert);
	free(*str);
	*str = tmp;
	*i = ft_strlen(*str) - ft_strlen((ft_strstr(*str, insert) + 
				ft_strlen(insert)));
	free(insert);
	return (0);
}
