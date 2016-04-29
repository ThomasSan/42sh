/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_list_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 16:49:41 by dbaldy            #+#    #+#             */
/*   Updated: 2016/04/29 19:46:56 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char			**tabl_completion(char *path)
{
	DIR				*dip;
	struct dirent	*files;
	char			**res;
	int				count;

	if ((dip = opendir(path)) == NULL)
		return (NULL);
	count = 0;
	while ((files = readdir(dip)))
		count++;
	closedir(dip);
	if (count == 0 ||
			(res = (char**)malloc(sizeof(char*) * (count + 1))) == NULL)
		return (NULL);
	res[count] = NULL;
	count = 0;
	dip = opendir(path);
	while ((files = readdir(dip)))
	{
		res[count] = file_suffix(files->d_name, path);
		count++;
	}
	closedir(dip);
	return (res);
}

static char			*alias_path(char *home, char *res)
{
	home = ft_strtrunc(res, '/');
	free(res);
	res = home;
	home = ft_strjoin(res, "/");
	free(res);
	res = home;
	return (res);
}

static char			*path_aliases_compl(char *buf)
{
	char	*res;
	char	*home;
	char	*tmp;

	res = ft_strdup(buf);
	if (ft_strncmp(res, "~/", 2) == 0 && (home = cd_var_env("HOME")) != NULL)
	{
		tmp = res;
		res = ft_strjoin(home, &(res[1]));
		free(tmp);
		free(home);
	}
	if (ft_strchr(res, '/') == NULL)
	{
		free(res);
		res = ft_strdup("./");
	}
	else
		res = alias_path(home, res);
	return (res);
}

char				*path_to_tab(char *var, int marge)
{
	int			i;
	int			count;
	char		*buf;

	i = g_local->curs - marge - 2;
	count = 1;
	if (i < 0 || (i == 0 && var[i] <= 32))
		return (NULL);
	if (var[i] != ' ' || (i > 1 && var[i] == ' ' && var[i - 1] == 0x5c))
	{
		while (var[i + 1] && ((var[i + 1] == ' ' && var[i] == 0x5c)
				|| var[i + 1] != ' '))
			i++;
		while (i > 1 && ((var[i - 1] == ' ' && i > 2 && var[i - 2] == 0x5c) ||
					var[i - 1] != ' '))
		{
			count++;
			i--;
		}
		buf = ft_strsub(var, i, count);
	}
	else
		buf = ft_strdup("./");
	return (buf);
}

char				**list_path(char *var, int marge)
{
	char		*buf;
	char		*res;
	char		**table;

	if ((buf = path_to_tab(var, marge)) == NULL)
		return (NULL);
	res = path_aliases_compl(buf);
	free(buf);
	table = tabl_completion(res);
	free(res);
	return (table);
}
