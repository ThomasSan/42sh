/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 15:22:50 by cbaldy            #+#    #+#             */
/*   Updated: 2016/04/23 15:01:23 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*cd_var_env(char *name)
{
	int		i;
	char	*tmp;

	if ((i = sh_is_new_var(name)) < 0)
	{
		ft_dprintf(STDERR_FILENO, "cd: %s not set\n", name);
		return (NULL);
	}
	tmp = ft_strdup(&(ft_strchr(g_env[i], '=')[1]));
	if (access(tmp, F_OK) < 0)
	{
		ft_dprintf(STDERR_FILENO, "cd: %s invalid path: %s\n", name, tmp);
		return (NULL);
	}
	return (tmp);
}

char		*cd_get_path(char **com, int opt)
{
	char	*path;
	int		dir;
	
	dir = (opt == 0 || com[1] == NULL ? 1 : 2);
	path = NULL;
	if (com[dir] == NULL)
		return (cd_var_env("HOME"));
	if (com[dir][0] == '/')
		return (ft_strdup(com[dir]));
	if (com[dir][0] == '~')
		if ((path = cd_var_env("HOME")) == NULL)
			return (NULL);
	if (com[dir][0] == '-')
		if ((path = cd_var_env("OLDPWD")) == NULL)
			return (NULL);
	if (path != NULL)
		return (mod_strjoin(path, &(com[dir][1]), 1));
	return (cd_env_cdpath(com, dir));
}

char		*cd_get_old_path(void)
{
	int		i;
	char	*path;
	char	*err;

	err = NULL;
	if ((i = sh_is_new_var("PWD")) < 0)
	{
		if ((path = getcwd(err, 0)) == NULL)
		{
			ft_dprintf(STDERR_FILENO, "cd: error %s", err);
			free(err);
			return (NULL);
		}
		return (path);
	}
	else
		return (ft_strdup(&(ft_strchr(g_env[i], '=')[1])));
}

char		*cd_print_path(char **com, char *n_path, int opt)
{
	char	*path;
	char	*home;
	int		i[2];

	i[0] = (opt == 0 || com[1] == NULL ? 1 : 2);
	path = NULL;
	if (com[i[0]] != NULL)
		if (com[i[0]][0] == '-' || opt == 3)
		{
			if ((i[1] = sh_is_new_var("HOME")) != -1)
			{
				home = &(ft_strchr(g_env[i[1]], '=')[1]);
				if (ft_strncmp(home, n_path, ft_strlen(home)) == 0)
					path = ft_strjoin("~", &(n_path[ft_strlen(home)]));
				else
					path = ft_strdup(n_path);
			}
			else
				path = ft_strdup(n_path);
		}
	return (path);
}
