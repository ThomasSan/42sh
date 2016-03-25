/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_and_or.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 11:51:07 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/25 13:47:17 by cbaldy           ###   ########.fr       */
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
		sh_interpret(root->left);
		close(fd[1]);
		exit(ret);
	}
	else if (pid > 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		wait(&i);
		ret = sh_interpret(root->right);
	}
	return (ret);
}

int		exec_and(t_tree *root)
{
	int		ret;

	if ((ret = sh_interpret(root->left)) > 0)
		return (ret);
	else
		return (sh_interpret(root->right));
}

int		exec_or(t_tree *root)
{
	int		ret;

	if ((ret = sh_interpret(root->left)) == 0)
		return (ret);
	else
		return (sh_interpret(root->right));
}
