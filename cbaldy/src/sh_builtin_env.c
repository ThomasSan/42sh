/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 15:51:57 by cbaldy            #+#    #+#             */
/*   Updated: 2016/02/15 10:25:36 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	env_print(void)
{
	int		i;

	i = 0;
	if (g_env[0] == NULL)
		ft_dprintf(STDOUT_FILENO, "env: env not set\n");
	else
	{
		i = 0;
		while (g_env[i] != NULL)
		{
			ft_dprintf(STDOUT_FILENO, "%s\n", g_env[i]);
			i++;
		}
	}
	return (0);
}

static void	env_exec_utility(char **com, int i)
{
	if (com[i] == NULL)
		env_print();
	else
		sh_command(&(com[i]));
	exit(0);
}

int			sh_builtin_env(char **com)
{
	int		i;
	pid_t	pid;

	if ((pid = fork()) < 0)
		return (ft_free_tab(com));
	if (pid == 0)
	{
		if ((i = env_custom(com)) < 0)
			exit(1);
		env_exec_utility(com, i);
	}
	else if (pid > 0)
		wait(&i);
	return (ft_free_tab(com));
}
