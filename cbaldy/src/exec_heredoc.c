/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 12:30:09 by cbaldy            #+#    #+#             */
/*   Updated: 2016/05/06 11:12:52 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			exec_heredoc(t_tree *root)
{
	int		fd[2];
	int		ret;

	if (g_local->le_mode == 1)
	{
		sh_reset_std_fd();
		ft_dprintf(STDERR_FILENO, "shell: no heredoc with this mode\n");
		exec_free_root(root->right);
		return (1);
	}
	pipe(fd);
	if (root->cmd[1] != NULL)
		ft_putstr_fd(root->cmd[1], fd[1]);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	ret = sh_interpret(root->right);
	close(fd[0]);
	return (ret);
}
