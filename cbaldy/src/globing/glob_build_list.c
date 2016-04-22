/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_build_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 18:55:47 by dbaldy            #+#    #+#             */
/*   Updated: 2016/04/22 18:23:46 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"

static int			alias_home(char **path)
{
	char	*home;
	char	*result;

	if (**path == '~')
	{
		if ((home = cd_var_env("HOME")) == NULL)
			return (0);
		else
		{
			result = ft_strjoin(home, &(path[0][1]));
			free(*path);
			free(home);
			*path = result;
		}
	}
	return (0);
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
	return (res);
}

t_glob_list			*build_match_list(char **path, char *word)
{
	char			**possibilities;
	int				i;
	t_glob_list		*glob;

	i = 0;
	alias_home(path);
	glob = NULL;
	if ((possibilities = tabl_compl(*path)) == NULL)
		return (NULL);
	while (possibilities[i])
	{
		if (match(possibilities[i], word) == 1 && (possibilities[i][0] != '.'
				|| word[0] == '.'))
			glob = add_elem_glob(*path, possibilities[i], glob);
		i++;
	}
	while (glob && glob->prev)
		glob = glob->prev;
	ft_free_tab(possibilities);
	return (glob);
}
