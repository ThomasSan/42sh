/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_build_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 18:55:47 by dbaldy            #+#    #+#             */
/*   Updated: 2016/04/26 11:52:12 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int					alias_home(char **path)
{
	char	*home;
	char	*result;

	if (**path == '~')
	{
		if ((home = cd_var_env("HOME")) == NULL)
			return (0);
		else
		{
			result = ft_strjoin(home, &(path[0][1]));
			free(*path);
			free(home);
			*path = result;
		}
	}
	return (0);
}

char				**tabl_compl(char *path)
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
		res[count] = ft_strdup(files->d_name);
		count++;
	}
	closedir(dip);
	return (res);
}