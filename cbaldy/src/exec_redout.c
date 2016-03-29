/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redout.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 12:09:42 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/29 14:48:50 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	exec_redout_get_fd(t_tree *root)
{
	char	*path;
	int		open_fd;
	int		opt;

	if ((path = cd_get_path2(root->cmd[1])) == NULL)
		return (-1);
	if (access(path, F_OK) == 0 && access(path, W_OK) < 0)
	{
		ft_dprintf(STDERR_FILENO, "shell: %s: permission denied\n",
				root->cmd[1]);
		free(path);
		return (-1);
	}
	opt = O_WRONLY | O_CREAT | (root->types == D_GREAT ? O_APPEND : O_TRUNC);
	if ((open_fd = open(path, opt, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
		ft_dprintf(STDERR_FILENO, "shell: %s: cannot write on this\n",
				root->cmd[1]);
	free(path);
	return (open_fd);
}

static int	exec_redout_g_and(t_tree *root)
{
	int		open_fd;

	if (root->types == G_AND)
	{
		if (root->cmd[1][0] > 48 && root->cmd[1][0] < 58)
		{
			if ((open_fd = ft_atoi(root->cmd[1])) > STDERR_FILENO)
			{
				ft_dprintf(STDERR_FILENO, "shell: %d: bad file descriptor\n",
						open_fd);
				return (-1);
			}
			else
				return (open_fd);
		}
	}
	return (exec_redout_get_fd(root));
}

int			exec_redout(t_tree *root)
{
	int		ret;
	int		fd[2];

	if (root->types == G_AND && root->cmd[1][0] == '-')
	{
		close(ft_atoi(root->cmd[0]));
		return (sh_interpret(root->right));
	}
	if ((fd[1] = exec_redout_g_and(root)) < 0)
		return (1);
	fd[0] = ft_atoi(root->cmd[0]);
	if (fd[0] >= g_std_fd[0] && fd[0] <= g_std_fd[2])
		fd[0] = STDOUT_FILENO;
	if (root->types == AND_G)
		dup2(fd[1], STDERR_FILENO);
	dup2(fd[1], fd[0]);
	ret = sh_interpret(root->right);
	close(fd[1]);
	return (ret);
}
