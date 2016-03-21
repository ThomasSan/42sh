/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_get_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 10:54:42 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/21 13:05:10 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int			hash_explore_dir(char *path, t_hash_tree **root)
{
	DIR				*dirp;
	struct dirent	*dp;

	if ((dirp = opendir(path)) != NULL)
	{
		while ((dp = readdir(dirp)) != NULL)
			if (dp->d_name[0] != '.' && dp->d_name[0] != '[')
				hash_build_tree(dp->d_name, path, root);
		closedir(dirp);
	}
	return (0);
}

int					hash_get_tab(void)
{
	char		**path;
	t_hash_tree	*root;
	int			i;

	if ((i = sh_is_new_var("PATH")) < 0)
		return (0);
	root = NULL;
	path = ft_strsplit(&(ft_strchr(g_env[i], '=')[1]), ':');
	i = 0;
	while (path[i] != NULL)
	{
		hash_explore_dir(path[i], &root);
		i++;
	}
	ft_free_tab(path);
	return (0);
}
