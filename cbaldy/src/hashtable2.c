/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 08:53:14 by nchrupal          #+#    #+#             */
/*   Updated: 2016/04/27 19:33:02 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <unistd.h>
#include "libft.h"
#include "hashtable.h"
#include "shell.h"

extern t_hash	*g_hashtable;

t_hash		*hash_insert(char *cmd, char *fullpath)
{
	unsigned	key;
	t_hash		*tmp;
	t_hash		*new;

	key = hash_key(cmd);
	tmp = g_hashtable + key;
	while (tmp->next != NULL)
		tmp = tmp->next;
	if (tmp->cmd[0] != '\0')
	{
		new = xmalloc(sizeof(*new));
		ft_bzero(new, sizeof(*new));
		tmp->next = new;
		tmp = new;
	}
	tmp->key = key;
	ft_strlcat(tmp->cmd, cmd, BUFF_SZ);
	ft_strlcat(tmp->fullpath, fullpath, BUFF_SZ);
	return (g_hashtable);
}

void		hash_addfile(char *path)
{
	struct dirent	*dp;
	DIR				*dirp;
	char			file[BUFF_SZ + 1];

	dirp = opendir(path);
	if (dirp == NULL)
		return ;
	while ((dp = readdir(dirp)) != NULL)
	{
		ft_strncpy(file, path, BUFF_SZ);
		ft_strlcat(file, "/", BUFF_SZ);
		ft_strlcat(file, dp->d_name, BUFF_SZ);
		if (ft_strcmp(dp->d_name, ".") != 0 &&
				ft_strcmp(dp->d_name, "..") != 0)
			hash_insert(dp->d_name, file);
	}
	closedir(dirp);
}

t_hash		*hash_createfile(void)
{
	char	**path;
	int		i;

	hash_del();
	g_hashtable = hash_new();
	if ((i = sh_is_new_var("PATH")) < 0)
		return (g_hashtable);
	path = ft_strsplit(&(ft_strchr(g_env[i], '=')[1]), ':');
	i = 0;
	while (path != NULL && path[i] != NULL)
	{
		hash_addfile(path[i]);
		i++;
	}
	ft_free_tab(path);
	return (g_hashtable);
}

t_hash		*hash_update(void)
{
	hash_del();
	return (hash_createfile());
}
