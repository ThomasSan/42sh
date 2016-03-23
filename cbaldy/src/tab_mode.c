/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_mode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 13:40:47 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/23 10:05:23 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_param		*string_matches(char *var, char **buf)
{
	size_t		size;
	int			i;
	t_param		*debut;
	t_param		*tmp;

	tmp = NULL;
	debut = NULL;
	size = ft_strlen(var);
	i = 0;
	while (buf[i])
	{
		if (ft_strncmp(var, buf[i], size) == 0)
			tmp = add_file(debut, buf[i]);
		if (tmp && tmp->prev == NULL)
			debut = tmp;
		i++;
	}
	debut->prev = tmp;
	tmp->next = debut;
	return (debut);
}

static char			**tabl_compl(char *path)
{
	DIR				*dip;
	struct dirent	*files;
	char			**res;
	int				count;

	if ((dip = opendir(path)) == NULL)
		return (NULL);
	count = 0;
	while ((files = readdir(dip)))
		count++;
	closedir(dip);
	if (count == 0 ||
			(res = (char**)malloc(sizeof(char*) * (count + 1))) == NULL)
		return (NULL);
	res[count] = NULL;
	count = 0;
	dip = opendir(path);
	while ((files = readdir(dip)))
	{
		res[count] = ft_strdup(files->d_name);
		count++;
	}
	closedir(dip);
	free(path);
	return (res);
}

static char			**list_path(char *var)
{
	char			*buf;
	int				count;
	char			*path;
	char			*res;

	count = 0;
	buf = ft_strrchr(var, ' ') + 1;
	buf = (ft_strchr(buf, '/') == NULL) ? ft_strdup(".") :
		ft_strtrunc(buf, '/');
	if (buf[0] == '~')
		if ((path = cd_var_env("HOME")) != NULL)
		{
			res = ft_strjoin(path, &buf[1]);
			free(buf);
			buf = res;
			free(path);
		}
	return (tabl_compl(buf));
}

static char			*word_to_tab(char *var)
{
	char	*word;
	int		i;
	
	if (iscommand(var) == 0)
		return (ft_strdup(var));
	i = 0;
	word = ft_strrchr(var, ' ') + 1;
	while (word[i])
		i++;
	while (i--)
		if (word[i] == '/' && i > 0)
			return (ft_strdup(&(word[i + 1])));
	return (ft_strdup(word));	
}

int					tab_mode(t_com_list *begin)
{
	t_param				*debut;
	char				*var;
	char				**table;
	char				*word;

	if (begin == NULL)
		return (0);
	if ((var = com_list_string(begin)) == NULL)
		return (0);
	table = (iscommand(var) == 0) ? g_hash : list_path(var);
	if (table == NULL)
		return (0);
	word = word_to_tab(var);
	if ((debut = string_matches(word, table)) == NULL && g_local->completion)
		exit_completion(begin);
	if (debut != NULL)
		tab_select(debut, begin);
	if (iscommand(var) != 0)
		ft_free_tab(table);
	free(var);
	free(word);
	return (0);
}
