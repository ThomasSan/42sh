/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 16:01:14 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/24 15:55:03 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_execute_bin(char *path, char **com)
{
	pid_t	pid;
	int		i;

	pid = fork();
	if (pid > 0)
	{
		wait(&i);
		return (i % 255);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		execve(path, com, g_env);
		ft_dprintf(STDERR_FILENO, "shell: exec format error: %s\n", com[0]);
		exit(126);
	}
	return (1);
}

int			sh_command(char **com)
{
	char	*path_to_bin;
	int		i;

	if ((path_to_bin = sh_get_exec_path(com[0])) == NULL)
		return (127);
	if (access(path_to_bin, X_OK) < 0)
	{
		ft_dprintf(STDERR_FILENO, "shell: permission denied: %s\n", com[0]);
		free(path_to_bin);
		return (126);
	}
	i = sh_execute_bin(path_to_bin, com);
	free(path_to_bin);
	return (i);
}
