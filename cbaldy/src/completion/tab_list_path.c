/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_list_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 16:49:41 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/26 18:26:49 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char			**tabl_compl(char *path)
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
	free(path);
	return (res);
}

static char			*path_aliases_compl(char *buf)
{
	char	*res;
	char	*home;

	res = ft_strdup(buf);
	if (ft_strncmp(res, "~/", 2) == 0 && (home = cd_var_env("HOME")) != NULL)
	{
		res = ft_strjoin(home, &(res[1]));
		free(home);
	}
	return (res);
}

char				*path_to_tab(char *var)
{
	int			i;
	int			count;
	char		*buf;

	i = g_local->curs - g_local->prompt - 1;
	if (i == 0)
		return (NULL);
	if ((var[i - 1] == ' ' && var[i] == '\0') || (var[i] == ' ' &&
				var[i + 1] == ' '))
		return (ft_strdup("./"));
	count = 0;
	while (var[i] && var[i] != ' ' && var[i + 1] && var[i + 1] != ' ')
		i++;
	while (var[i] != ' ' && i > 0)
	{
		count++;
		i--;
	}
	if (i >= 0 && var[i] == ' ')
		i++;
	buf = ft_strsub(var, i, count);
	return (buf);
}

char				**list_path(char *var)
{
	char		*buf;
	char		*res;

	if ((buf = path_to_tab(var)) == NULL)
		return (NULL);
	res = path_aliases_compl(buf);
	free(buf);
	return (tabl_compl(res));
}
