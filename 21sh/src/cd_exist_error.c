/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_exist_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 13:40:38 by cbaldy            #+#    #+#             */
/*   Updated: 2016/04/26 19:20:40 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	cd_check_path_name(char *str, char *dir)
{
	if (str != NULL)
		if (ft_strlen(str) > PATH_MAX)
		{
			ft_dprintf(STDERR_FILENO, "cd: path name too long: %s\n", str);
			return (-1);
		}
	if (ft_strlen(dir) > NAME_MAX)
	{
		ft_dprintf(STDERR_FILENO, "cd: directory name too long: %s\n", dir);
		return (-1);
	}
	return (0);
}

static int	cd_check_rights(char *str, char *dir)
{
	char			*path;
	int				i;
	struct stat		buf;

	i = 1;
	path = mod_strjoin(ft_strjoin(str, "/"), dir, 1);
	if (lstat(path, &buf) == -1 || ((buf.st_mode & S_IFDIR) == 0 &&
		S_ISLNK(buf.st_mode) == 0))
		i = -ft_dprintf(STDERR_FILENO, "cd: not a directory: ", str);
	else if (access(path, F_OK) < 0)
		i = -ft_dprintf(STDERR_FILENO,
				"cd: too many levels of symbolic links: ");
	else if (access(path, X_OK) < 0)
		i = -ft_dprintf(STDERR_FILENO, "cd: permission denied: ", path);
	free(path);
	return (i);
}

static int	cd_check_dir(char *str, char *dir)
{
	DIR				*dirp;
	struct dirent	*dp;
	int				found;

	found = 0;
	if (cd_check_path_name(str, dir) == -1)
		return (-1);
	if ((dirp = opendir(str)) == NULL)
		return (-ft_dprintf(STDERR_FILENO, "cd: directory not accessible: "));
	while ((dp = readdir(dirp)) != NULL && found == 0)
	{
		if (ft_strcmp(dp->d_name, dir) == 0)
			found = cd_check_rights(str, dir);
	}
	if (found == 0)
		ft_dprintf(STDERR_FILENO, "cd: no such file or directory: ");
	closedir(dirp);
	return (found);
}

static int	cd_check_path(char *path)
{
	char	**arr;
	char	*str;
	int		i[2];

	arr = ft_strsplit(path, '/');
	str = ft_strdup("/");
	i[0] = 0;
	i[1] = 1;
	while (arr[i[0]] != NULL && i[1] > 0)
	{
		i[1] = cd_check_dir(str, arr[i[0]]);
		if (i[0] != 0)
			str = mod_strjoin(mod_strjoin(str, "/", 1), arr[i[0]], 1);
		else
			str = mod_strjoin(str, arr[i[0]], 1);
		i[0]++;
	}
	free(str);
	ft_free_tab(arr);
	return (i[1]);
}

int			cd_exist_error(char *path, char *com, int flag)
{
	if (cd_check_path(path) > 0)
		ft_dprintf(STDERR_FILENO, "cd: An error occured: %s\n", com);
	else
	{
		if (flag == 0)
			ft_dprintf(STDERR_FILENO, "%s\n", com);
		else
			ft_dprintf(STDERR_FILENO, "%s\n", path);
	}
	return (0);
}
