/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_build_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 18:55:47 by dbaldy            #+#    #+#             */
/*   Updated: 2016/04/26 14:50:43 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"

int					alias_ihome(char **path, int i)
{
	char	*result;
	int		j;

	if ((j = sh_is_new_var("HOME")) < 0)
		return (0);
	result = ft_strchr(g_env[j], '=') + 1;
	result = ft_ireplace_str(*path, result, i, 1);
	free(*path);
	*path = result;
	return (0);
}

int					alias_home(char **path)
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

char				**tabl_compl(char *path)
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

static int			is_dir(char *path, char *poss)
{
	char		*tmp;
	struct stat	*isdir;

	if ((isdir = (struct stat*)malloc(sizeof(struct stat))) == NULL)
		return (-1);
	tmp = ft_strjoin(path, poss);
	stat(tmp, isdir);
	free(tmp);
	if ((isdir->st_mode & S_IFDIR) == 0)
	{
		free(isdir);
		return (-1);
	}
	free(isdir);
	return (0);
}

char				**build_match_list(char *path, char *word, char *next)
{
	char			**poss;
	int				i;
	char			**matches;

	i = 0;
	matches = NULL;
	if ((poss = tabl_compl(path)) == NULL)
		return (NULL);
	while (poss[i])
	{
		if (next != NULL && is_dir(path, poss[i]) == 0)
			;
		else if (match(poss[i], word) == 1)
		{
			if ((poss[i][0] == '.' && word[0] != '.') || ft_strcmp(poss[i], ".")
					== 0 || ft_strcmp(poss[i], "..") == 0)
				;
			else
				ft_array_push(&matches, poss[i]);
		}
		i++;
	}
	i = 0;
	while (matches[i])
	{
		ft_printf("matches:%s\n", matches[i]);
		i++;
	}
	ft_free_tab(poss);
	return (matches);
}
