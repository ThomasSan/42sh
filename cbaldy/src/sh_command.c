/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 16:01:14 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/08 17:26:13 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_execute_bin(char *path, char **com)
{
	pid_t	pid;
	int		i;

	if ((pid = fork()) < 0)
		ft_dprintf(STDERR_FILENO, "%s: an error occured\n", com[0]);
	if (pid > 0)
	{
		wait(&i);
		free(path);
		return (i);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		execve(path, com, g_env);
		ft_dprintf(STDERR_FILENO, "%s: an error occured\n", com[0]);
		exit(1);
	}
	return (0);
}

static char	*sh_explore_bin(char *list_path, char *bin)
{
	DIR				*dirp;
	struct dirent	*dp;
	char			*exec;

	exec = NULL;
	if ((dirp = opendir(list_path)) != NULL)
	{
		while ((dp = readdir(dirp)) != NULL)
			if (ft_strncmp(bin, dp->d_name, ft_strlen(dp->d_name)) == 0 &&
					bin[ft_strlen(dp->d_name)] == '\0')
			{
				exec = mod_strjoin(ft_strjoin(list_path, "/"), bin, 1);
				break ;
			}
		closedir(dirp);
	}
	return (exec);
}

static int	sh_direct_call(char **com)
{
	char	*path;

	if (com[0][0] == '/')
		path = ft_strdup(com[0]);
	else
	{
		if ((path = getcwd(NULL, 0)) == NULL)
			return (-1);
		path = mod_strjoin(mod_strjoin(path, "/", 1), com[0], 1);
	}
	if (path != NULL)
	{
		if (access(path, X_OK) == 0)
			return (sh_execute_bin(path, com));
	}
	free(path);
	return (-1);
}

int			sh_command(char **com)
{
	int		i;
	char	*exec;
	char	**path;

	if ((i = sh_direct_call(com)) != -1)
		return (i);
	i = sh_is_new_var("PATH");
	path = (i != -1 ? ft_strsplit(&(ft_strchr(g_env[i], '=')[1]), ':') :
			ft_strsplit("", ' '));
	i = 0;
	while (path[i] != NULL)
	{
		if ((exec = sh_explore_bin(path[i], com[0])) != NULL)
		{
			ft_free_tab(path);
			return (sh_execute_bin(exec, com));
		}
		i++;
	}
	ft_dprintf(STDERR_FILENO, "shell: command not found: %s\n", com[0]);
	if (path != NULL)
		ft_free_tab(path);
	return (0);
}
