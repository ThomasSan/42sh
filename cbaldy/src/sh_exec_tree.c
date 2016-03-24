/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exec_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 12:10:21 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/24 11:14:12 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		exec_pipe(t_tree *root)
{
	int		fd[2];
	pid_t	pid;
	int		i;
	int		ret;

	pipe(fd);
	ret = 0;
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		ret = sh_interpret(root->left);
		close(fd[1]);
		exit(ret);
	}
	else if (pid > 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		ret = sh_interpret(root->right);
		wait(&i);
	}
	return (ret);
}

int		exec_redout(t_tree *root)
{
	int		open_fd;
	mode_t	mode;
	int		opt;
	int		ret;

	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	opt = O_WRONLY | O_CREAT;
	if (root->types == 4)
		opt |= O_APPEND;
	else if (root->types == 2)
		opt |= O_TRUNC;
	open_fd = open(root->cmd[0], opt, mode);
	dup2(open_fd, STDOUT_FILENO);
	ret = sh_interpret(root->left);
	close(open_fd);
	return (ret);
}
