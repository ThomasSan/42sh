/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 10:56:23 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/14 18:00:50 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char				*verif_exe(char *command, int type)
{
	if (access(command, F_OK) == 0 && access(command, X_OK) == 0)
		return ((type == 0) ? ft_strdup(command) : ft_mypwd(command));
	else if (access(command, X_OK) == -1 && access(command, F_OK) == 0)
	{
		free(g_err);
		g_err = ft_strdup("minishell: permission denied:");
	}
	return (NULL);
}

static char			*test_bin(char *command, char *tabl)
{
	DIR				*dire;
	struct dirent	*dp;
	char			*ret;

	ret = NULL;
	if ((dire = opendir(tabl)) == NULL)
		return (NULL);
	while ((dp = readdir(dire)) != NULL && ret == NULL)
		if (ft_strcmp(dp->d_name, command) == 0)
			ret = ft_strjoin_multiple(3, tabl, "/", command);
	if (closedir(dire) < 0)
		exit(1);
	return (ret);
}

static char			*bin_existence(char *command)
{
	char		*env_path;
	char		**tabl;
	char		*ret;
	int			i;

	i = 0;
	ret = NULL;
	if ((env_path = get_env_var("PATH")) == NULL)
		return (NULL);
	tabl = ft_strsplit(env_path, ':');
	free(env_path);
	while (tabl[i] && ret == NULL)
	{
		ret = test_bin(command, tabl[i]);
		i++;
	}
	ft_freetab(tabl);
	return (ret);
}

char				*find_path(char **tabl)
{
	char	*ret;

	to_lower(&tabl[0]);
	if (tabl[0][0] == '/')
		ret = verif_exe(tabl[0], 0);
	else if (ft_strchr(tabl[0], '/') != NULL &&
			(ret = verif_exe(tabl[0], 0)) != NULL)
		;
	else
		ret = bin_existence(tabl[0]);
	return (ret);
}
