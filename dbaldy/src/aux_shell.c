/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/27 16:30:58 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/15 11:51:47 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			size_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
}

char		*check_length(char *to_check, char *path)
{
	char	*err;

	err = NULL;
	if (ft_strlen(to_check) > NAME_MAX || ft_strlen(path) > PATH_MAX)
		err = ft_strdup("cd: File name too long:");
	return (err);
}

char		**my_pwd(char *pwd)
{
	char	**res;
	char	**buf;
	int		size;

	buf = ft_strsplit(pwd, '/');
	size = size_tab(buf);
	if ((res = (char**)malloc(sizeof(char*) * (size + 2))) == NULL)
		exit(1);
	res[0] = ft_strdup("");
	copy_tab(&res[1], buf);
	ft_freetab(buf);
	return (res);
}

void		copy_tab(char **tab, char **env)
{
	int		i;

	i = 0;
	while (env[i] != NULL)
	{
		tab[i] = ft_strdup(env[i]);
		i++;
	}
	tab[i] = NULL;
}

void		reduce_next(t_env *buf)
{
	while (buf != NULL)
	{
		buf->nb -= 1;
		buf = buf->next;
	}
}
