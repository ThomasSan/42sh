/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exec_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 12:10:21 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/23 12:19:04 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		exec_cmd(t_tree *root)
{
	sh_execute(root->cmd);
	return (0);
}

int		exec_pipe(t_tree *root)
{
	int		fd[2];
	pid_t	pid;
	int		i;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		sh_interpret(root->left);
		close(fd[1]);
		exit(0);
	}
	else if (pid > 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		sh_interpret(root->right);
		wait(&i);
	}
	return (0);
}

int		exec_redout(t_tree *root)
{
	int		open_fd;
	mode_t	mode;
	int		opt;

	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	opt = O_WRONLY | O_CREAT;
	if (root->types == 4)
		opt |= O_APPEND;
	else if (root->types == 2)
		opt |= O_TRUNC;
	open_fd = open(root->cmd[0], opt, mode);
	dup2(open_fd, STDOUT_FILENO);
	sh_interpret(root->left);
	close(open_fd);
	return (0);
}
