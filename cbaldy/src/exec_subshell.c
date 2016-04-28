/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 13:37:40 by cbaldy            #+#    #+#             */
/*   Updated: 2016/04/28 14:29:46 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		exec_subshell(t_tree *root)
{
	pid_t	pid;
	int		ret;

	ret = 1;
	pid = fork();
	if (pid == 0)
	{
		ret = sh_interpret(root->right);
		exit(ret);
	}
	else if (pid > 0)
	{
		wait(&ret);
		exec_free_root(root->right);
	}
	return (ret);
}
