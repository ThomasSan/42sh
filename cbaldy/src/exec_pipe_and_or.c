/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_and_or.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 11:51:07 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/29 17:24:33 by cbaldy           ###   ########.fr       */
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
		ret = sh_interpret(root->right);
		wait(&i);
	}
	return (ret);
}

int		exec_and(t_tree *root)
{
	int		ret;

	if ((ret = sh_interpret(root->left)) > 0)
		return (ret);
	else
	{
		sh_reset_std_fd();
		return (sh_interpret(root->right));
	}
}

int		exec_or(t_tree *root)
{
	int		ret;

	if ((ret = sh_interpret(root->left)) == 0)
		return (ret);
	else
	{
		sh_reset_std_fd();
		return (sh_interpret(root->right));
	}
}

int		exec_end(t_tree *root)
{
	char	*ret;
	int		i;

	i = sh_interpret(root->left);
	ret = ft_itoa(i);
	if ((sh_change_var_env("?", ret)) == -1)
		sh_add_var_env("?", ret);
	free(ret);
	sh_reset_std_fd();
	if (root->right != NULL)
		return (sh_interpret(root->right));
	else
		return (i);
}
