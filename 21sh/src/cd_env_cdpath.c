/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_env_cdpath.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/23 13:12:43 by dbaldy            #+#    #+#             */
/*   Updated: 2016/04/23 15:11:24 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*cd_opt_path(char **com, int dir)
{
	char	*err;
	char	*path;
	int		i;

	if ((i = sh_is_new_var("PWD")) < 0)
	{
		err = NULL;
		if ((path = getcwd(err, 0)) == NULL)
		{
			ft_dprintf(STDERR_FILENO, "cd: error %s", err);
			free(err);
			return (NULL);
		}
	}
	else
		path = &(ft_strchr(g_env[i], '=')[1]);
	return (mod_strjoin(ft_strjoin(path, "/"), com[dir], 1));
}

static char	*is_dir_in_path(char *path, char *operand)
{
	char	**poss;
	int		i;
	char	*res;
	char	*tmp;

	i = 0;
	res = NULL;
	if ((poss = tabl_compl(path)) == NULL)
		return (NULL);
	while (poss[i] && ft_strcmp(poss[i], operand) != 0)
		i++;
	if (poss[i])
	{
		if (poss[i][ft_strlen(poss[i]) - 1] != '/')
		{
			tmp = poss[i];
			poss[i] = ft_strjoin(tmp, "/");
			free(tmp);
		}
		res = ft_strjoin_multiple(3, path, "/", operand);
	}
	ft_free_tab(poss);
	return (res);
}

static char	*retrieve_cdpath(int i, char **com, int dir)
{
	char		*cdpath;
	char		**prefs;
	char		*res;

	cdpath = ft_strdup(ft_strchr(g_env[i], '=') + 1);
	prefs = ft_strsplit(cdpath, ':');
	i = 0;
	res = NULL;
	while (prefs[i])
	{
		alias_home(&(prefs[i]));
		if ((res = is_dir_in_path(prefs[i], com[dir])) != NULL)
			break ;
		i++;
	}
	ft_free_tab(prefs);
	free(cdpath);
	return (res);
}

char		*cd_env_cdpath(char **com, int dir)
{
	int			i;
	char		*res;
	char		*tmp;

	res = NULL;
	if ((i = sh_is_new_var("CDPATH")) < 0)
		return (cd_opt_path(com, dir));
	else
		res = retrieve_cdpath(i, com, dir);
	if (res == NULL)
		ft_dprintf(STDERR_FILENO, "cd: no such file or directory: %s\n",
				com[dir]);
	else if (res[0] == '/')
		return (res);
	else
	{
		tmp = com[dir];
		com[dir] = res;
		free(tmp);
	}
	return (cd_opt_path(com, dir));
}
