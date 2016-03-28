/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redin_redout.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 11:50:44 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/28 19:40:59 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int exec_redout_get_fd(t_tree *root)
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

int		exec_redout(t_tree *root)
{
	int		ret;
	int		open_fd;
	int		out_fd;

	if (root->types == G_AND && root->cmd[1][0] > 48 && root->cmd[1][0] < 58)
		open_fd = ft_atoi(root->cmd[1]);
	else if ((open_fd = exec_redout_get_fd(root)) < 0)
		return (1);
	out_fd = ft_atoi(root->cmd[0]);
	if (out_fd >= g_std_fd[0] && out_fd <= g_std_fd[2])
		out_fd = STDOUT_FILENO;
	if (root->types == AND_G)
		dup2(open_fd, STDERR_FILENO);
	dup2(open_fd, out_fd);
	ret = sh_interpret(root->right);
	close(open_fd);
	return (ret);
}

static char *exec_redin_get_path(t_tree *root)
{
	char	*path;

	if ((path = getcwd(NULL, 0)) == NULL)
		return (NULL);
	path = mod_strjoin(mod_strjoin(path, "/", 1), root->cmd[0], 1);
	if (access(path, F_OK) < 0)
	{
		ft_dprintf(STDERR_FILENO, "shell: %s: no such file or directory\n",
				root->cmd[0]);
		free(path);
		return (NULL);
	}
	if (access(path, R_OK) < 0)
	{
		ft_dprintf(STDERR_FILENO, "shell: %s: permission denied\n",
				root->cmd[0]);
		free(path);
		return (NULL);
	}
	return (path);
}

int		exec_redin(t_tree *root)
{
	int		open_fd;
	int		ret;
	char	*path;

	if ((path = exec_redin_get_path(root)) == NULL)
		return (1);
	if ((open_fd = open(path, O_RDONLY)) < 0)
	{
		ft_dprintf(STDERR_FILENO,
				"shell: %s: cannot read from here\n", root->cmd[0]);
		free(path);
		return (1);
	}
	dup2(open_fd, STDIN_FILENO);
	ret = sh_interpret(root->right);
	close(STDIN_FILENO);
	close(open_fd);
	free(path);
	return (ret);
}
