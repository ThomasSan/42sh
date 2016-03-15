/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_substitution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/14 18:18:57 by cbaldy            #+#    #+#             */
/*   Updated: 2016/02/15 10:24:55 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*cd_rebuild_path(char *path, char *s1, char *s2)
{
	char	**split;
	char	*new_path;
	int		i;

	split = ft_strsplit(path, '/');
	i = 0;
	new_path = ft_strdup("/");
	while (split[i] != NULL)
	{
		if (new_path[ft_strlen(new_path) - 1] != '/')
			new_path = mod_strjoin(new_path, "/", 1);
		if (ft_strcmp(split[i], s1) == 0)
			new_path = mod_strjoin(new_path, s2, 1);
		else
			new_path = mod_strjoin(new_path, split[i], 1);
		i++;
	}
	ft_free_tab(split);
	return (new_path);
}

static char	*cd_sub_path(char *s1, char *s2)
{
	char	*path;
	char	*new_path;

	path = (sh_is_new_var("PWD") < 0 ? getcwd(NULL, 0) :
			ft_strdup(&(ft_strchr(g_env[sh_is_new_var("PWD")], '=')[1])));
	if (path == NULL)
		return (NULL);
	if (ft_strstr(path, s1) == NULL)
	{
		ft_dprintf(STDERR_FILENO, "cd: string not in pwd: %s \n", s1);
		free(path);
		return (NULL);
	}
	new_path = cd_rebuild_path(path, s1, s2);
	free(path);
	return (new_path);
}

int			cd_substitution(char **com)
{
	char	*new_path;
	char	*old_path;
	char	*print_path;
	int		i;

	if (com[3] != NULL)
		return (-ft_dprintf(STDERR_FILENO, "cd: too many arguments\n"));
	if ((new_path = cd_sub_path(com[1], com[2])) == NULL)
		return (-1);
	old_path = cd_get_old_path();
	if ((i = chdir(new_path)) != 0)
		cd_exist_error(new_path, com[2], 1);
	else
		cd_update_env(old_path, new_path, 0);
	if ((print_path = cd_print_path(com, new_path, 3)) != NULL && i == 0)
		ft_dprintf(STDOUT_FILENO, "%s\n", print_path);
	if (print_path != NULL)
		free(print_path);
	free(new_path);
	free(old_path);
	return (-1);
}
