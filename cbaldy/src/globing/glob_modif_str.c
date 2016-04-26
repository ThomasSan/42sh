/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_modif_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 18:48:50 by dbaldy            #+#    #+#             */
/*   Updated: 2016/04/26 13:53:21 by dbaldy           ###   ########.fr       */
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

static char		*full_glob(t_glob_list *match_list)
{
	char		*tmp;
	t_glob_list *list_buf;
	char		*insert;

	list_buf = match_list;
	insert = ft_strdup("");
	while (list_buf)
	{
		tmp = ft_strdup(insert);
		free(insert);
		insert = (ft_strcmp(tmp, "") == 0) ? ft_strdup(list_buf->var) :
			ft_strjoin_multiple(4, tmp, " ", list_buf->var);
		free(tmp);
		list_buf = list_buf->next;
	}
	return (insert);
}

int				glob_modif_str(char **str, t_glob_list *match_list, char *word)
{
	char		*insert;
	char		*tmp;

	insert = full_glob(match_list);
	tmp = ft_replace_str(*str, word, insert);
	free(*str);
	*str = tmp;
	free(insert);
	return (0);
}
