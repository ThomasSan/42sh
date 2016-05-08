/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_get_exec_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 13:45:30 by cbaldy            #+#    #+#             */
/*   Updated: 2016/05/08 16:47:27 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "hashtable.h"

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
	t_hash	*hash;
	t_hash	*find;

	if ((i = sh_is_new_var("PATH")) < 0)
		return (NULL);
	hash = hash_createfile();
	find = hash_exist(cmd);
	if (find != NULL)
		return (ft_strdup(find->fullpath));
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
