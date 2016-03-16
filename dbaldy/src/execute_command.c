/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 12:34:18 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/14 18:02:01 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void			change_tilde(char *buf, char **new)
{
	int			i;
	char		*old;

	i = 0;
	while (new[i])
	{
		if (new[i][0] == '~' && (new[i][1] == '/' || new[i][1] == '\0'))
		{
			old = ft_strdup(&new[i][1]);
			free(new[i]);
			new[i] = ft_strjoin(buf, old);
			free(old);
		}
		i++;
	}
}

int					get_aliases(char **tabl)
{
	char	*buf;
	int		i;

	i = 0;
	while (tabl[i])
	{
		tabl[i] = free_quotes(tabl[i]);
		i++;
	}
	if ((buf = get_env_var("HOME")) == NULL)
		return (-1);
	change_tilde(buf, tabl);
	free(buf);
	return (0);
}

int					to_lower(char **str)
{
	int		i;

	i = 0;
	while ((*str)[i])
	{
		(*str)[i] = ft_tolower((*str)[i]);
		i++;
	}
	return (0);
}

static int			prg_fils(char *command, char **tabl, char **my_env)
{
	pid_t	father;
	int		ret;

	ret = 0;
	father = fork();
	if (father == 0)
	{
		signal(SIGINT, SIG_DFL);
		execve(command, tabl, my_env);
		free_env(&g_env);
		ft_dprintf(STDERR_FILENO, "minishell: permission denied: %s\n",
				command);
		return (-1);
	}
	if (father > 0)
		wait(&ret);
	return (0);
}

int					execute_command(char **tabl, char *path)
{
	int		ret;
	char	**my_env;

	my_env = retrieve_env(g_env);
	get_aliases(tabl);
	ret = prg_fils(path, tabl, my_env);
	ft_freetab(my_env);
	return (ret);
}
