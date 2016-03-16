/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 15:39:56 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/14 18:01:26 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*check_rights(char *to_check, char *elem)
{
	struct stat *buf;
	char		*err;
	char		*path;

	path = (ft_strcmp(to_check, "/") == 0) ? ft_strjoin(to_check, elem) :
		ft_strjoin_multiple(3, to_check, "/", elem);
	if ((err = check_length(to_check, path)) != NULL)
	{
		free(path);
		return (err);
	}
	if ((buf = (struct stat *)malloc(sizeof(struct stat))) == NULL)
		return (NULL);
	if ((lstat(path, buf)) == -1)
		return (NULL);
	if ((buf->st_mode & S_IFDIR) == 0 && (buf->st_mode & S_IFLNK) == 0)
		err = ft_strdup("cd: not a directory:");
	else if (access(path, F_OK) == -1)
		err = ft_strdup("cd: too many levels of symbolic links:");
	else if (access(path, X_OK) == -1)
		err = ft_strdup("cd: permission denied:");
	free(buf);
	free(path);
	return (err);
}

static char		*check_path(char *elem, char *pwd)
{
	DIR				*dip;
	struct dirent	*jc;

	if ((dip = opendir(pwd)) == NULL)
		return (ft_strdup("cd: not a directory:"));
	while ((jc = readdir(dip)) != NULL)
	{
		if (ft_strcmp(jc->d_name, elem) == 0)
		{
			closedir(dip);
			return (check_rights(pwd, elem));
		}
	}
	closedir(dip);
	return (ft_strdup("cd: no such file or directory:"));
}

static char		*path_to_check(char *path)
{
	char		*pwd;
	char		*buf;

	if (path[0] == '.')
	{
		buf = get_env_var("PWD");
		pwd = ft_strjoin(buf, &path[1]);
		free(buf);
	}
	else
		pwd = ft_strdup(path);
	return (pwd);
}

static void		check_file(char *path)
{
	char		*pwd;
	char		**tabl;
	int			i;
	char		*buf;
	char		*err;

	pwd = path_to_check(path);
	tabl = my_pwd(pwd);
	buf = ft_strdup("");
	i = 0;
	while (tabl[i] != NULL)
	{
		free(pwd);
		pwd = ft_strjoin_multiple(3, buf, "/", tabl[i]);
		if ((err = check_path(tabl[i + 1], pwd)) != NULL)
			break ;
		free(buf);
		buf = (i > 0) ? ft_strdup(pwd) : ft_strdup("");
		i++;
	}
	ft_freetab(tabl);
	free(pwd);
	free(buf);
	ft_dprintf(STDERR_FILENO, "%s %s\n", err, g_operand);
	free(err);
}

int				change_dir(char **tabl)
{
	char	*operand;
	char	*curpath;
	char	*pwd;

	get_aliases(tabl);
	if ((operand = get_operand(tabl)) == NULL)
		return (0);
	if ((curpath = get_path(operand)) == NULL)
	{
		free(operand);
		return (0);
	}
	g_operand = operand;
	pwd = get_pwd(tabl);
	if (chdir(curpath) == 0)
		change_pwd(operand, pwd, tabl);
	else
		check_file(curpath);
	free(operand);
	free(curpath);
	free(pwd);
	return (0);
}
