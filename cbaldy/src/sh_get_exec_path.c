/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_get_exec_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 13:45:30 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/25 11:53:42 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*sh_explore_dir(char *list_path, char *bin)
{
	DIR				*dirp;
	struct dirent	*dp;
	char			*exec;

	exec = NULL;
	if ((dirp = opendir(list_path)) != NULL)
	{
		while ((dp = readdir(dirp)) != NULL && exec == NULL)
		{
			if (ft_strcmp(bin, dp->d_name) == 0)
				exec = mod_strjoin(ft_strjoin(list_path, "/"), bin, 1);
		}
		closedir(dirp);
	}
	return (exec);
}

static char	*sh_direct_call(char *cmd)
{
	char	*path;

	if (cmd[0] == '/')
		path = ft_strdup(cmd);
	else
	{
		if ((path = getcwd(NULL, 0)) == NULL)
			return (NULL);
		path = mod_strjoin(mod_strjoin(path, "/", 1), cmd, 1);
	}
	if (path != NULL)
		if (access(path, F_OK) < 0)
		{
			free(path);
			path = NULL;
		}
	return (path);
}

static char	*sh_find_exec_path(char *cmd)
{
	int		i;
	char	**path;
	char	*bin;

	if ((i = sh_is_new_var("PATH")) < 0)
		return (NULL);
	path = ft_strsplit(&(ft_strchr(g_env[i], '=')[1]), ':');
	i = 0;
	while (path[i] != NULL)
	{
		if ((bin = sh_explore_dir(path[i], cmd)) != NULL)
		{
			ft_free_tab(path);
			return (bin);
		}
		i++;
	}
	ft_free_tab(path);
	return (NULL);
}

char		*sh_get_exec_path(char *cmd)
{
	char	*bin;

	bin = NULL;
	if (ft_strchr(cmd, '/') != NULL)
	{
		if ((bin = sh_direct_call(cmd)) == NULL)
			ft_dprintf(STDERR_FILENO,
					"shell: no such file or directory: %s\n", cmd);
	}
	else if ((bin = sh_find_exec_path(cmd)) == NULL)
		ft_dprintf(STDERR_FILENO, "shell: command not found: %s\n", cmd);
	return (bin);
}
