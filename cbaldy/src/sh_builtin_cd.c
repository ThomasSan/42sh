/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 15:51:04 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/24 15:55:35 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*cd_clean_path(char *path, int plus)
{
	char	*clean;
	char	**split;
	int		i;

	split = ft_strsplit(path, '/');
	i = 0;
	clean = ft_strdup("/");
	while (split[i] != NULL && split[i + plus] != NULL)
	{
		if (clean[ft_strlen(clean) - 1] != '/')
			clean = mod_strjoin(clean, "/", 1);
		if (ft_strcmp(split[i], "..") == 0)
			clean = cd_clean_path(clean, 1);
		else if (ft_strcmp(split[i], ".") != 0)
			clean = mod_strjoin(clean, split[i], 1);
		i++;
	}
	if (plus == 1)
		free(path);
	ft_free_tab(split);
	return (clean);
}

int			cd_update_env(char *old_path, char *new_path, int opt)
{
	char	*used;

	if (opt != 2)
		used = cd_clean_path(new_path, 0);
	else if ((used = getcwd(NULL, 0)) == NULL)
		used = cd_clean_path(new_path, 0);
	if ((sh_change_var_env("PWD", used)) == -1)
		sh_add_var_env("PWD", used);
	if (old_path != NULL)
		if ((sh_change_var_env("OLDPWD", old_path)) == -1)
			sh_add_var_env("OLDPWD", old_path);
	free(used);
	return (0);
}

static int	cd_read_opt(char **com)
{
	int		i[2];

	i[0] = 1;
	if (com[1] != NULL)
	{
		if (com[1][0] != '-' || ft_strcmp(com[1], "-") == 0)
			i[0] = 0;
		i[1] = 1;
		while (com[1][i[1]] != '\0' && i[0] != 0)
		{
			if (com[1][i[1]] == 'L')
				i[0] = 1;
			else if (com[1][i[1]] == 'P')
				i[0] = 2;
			else
				i[0] = 0;
			i[1]++;
		}
		if (i[0] == 0 && com[2] != NULL)
			return (cd_substitution(com));
	}
	return (i[0]);
}

int			sh_builtin_cd(char **com)
{
	char	*old_path;
	char	*new_path;
	char	*print_path;
	int		opt[2];

	if ((opt[0] = cd_read_opt(com)) < 0)
		return (1);
	if ((new_path = cd_get_path(com, opt[0])) == NULL)
		return (1);
	old_path = cd_get_old_path();
	if ((opt[1] = chdir(new_path)) != 0)
		cd_exist_error(new_path, com[1], 0);
	else
		cd_update_env(old_path, new_path, opt[0]);
	if ((print_path = cd_print_path(com, new_path, opt[0])) != NULL)
		ft_dprintf(STDOUT_FILENO, "%s\n", print_path);
	if (print_path != NULL)
		free(print_path);
	free(old_path);
	free(new_path);
	return (-opt[1]);
}
