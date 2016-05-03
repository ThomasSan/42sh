/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 15:51:57 by cbaldy            #+#    #+#             */
/*   Updated: 2016/05/03 10:30:33 by cbaldy           ###   ########.fr       */
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
	int		ret;

	ret = 0;
	if (com[i] == NULL)
		env_print();
	else
		ret = sh_execute(&(com[i]));
	exit(ret);
}

int			sh_builtin_env(char **com)
{
	int		i;
	pid_t	pid;

	i = 0;
	if ((pid = fork()) < 0)
		return (ft_free_tab(com) + 1);
	if (pid == 0)
	{
		if ((i = env_custom(com)) < 0)
			exit(1);
		env_exec_utility(com, i);
	}
	else if (pid > 0)
		wait(&i);
	return (i % 255);
}
