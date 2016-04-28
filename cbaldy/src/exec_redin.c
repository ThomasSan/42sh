/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 12:10:32 by cbaldy            #+#    #+#             */
/*   Updated: 2016/04/28 18:59:34 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	exec_redin_get_path(t_tree *root)
{
	char	*path;
	int		open_fd;

	if ((path = cd_get_path2(root->cmd[0])) == NULL)
		return (-1);
	if (access(path, F_OK) < 0)
	{
		ft_dprintf(STDERR_FILENO, "shell: %s: no such file or directory\n",
				root->cmd[0]);
		free(path);
		return (-1);
	}
	if (access(path, R_OK) < 0)
	{
		ft_dprintf(STDERR_FILENO, "shell: %s: permission denied\n",
				root->cmd[0]);
		free(path);
		return (-1);
	}
	if ((open_fd = open(path, O_RDONLY)) < 0)
		ft_dprintf(STDERR_FILENO,
				"shell: %s: cannot read from here\n", root->cmd[0]);
	free(path);
	return (open_fd);
}

static int	exec_redin_l_and(t_tree *root)
{
	int		open_fd;

	if (root->types == L_AND)
	{
		if (root->cmd[0][0] > 48 && root->cmd[1][0] < 58)
		{
			if ((open_fd = ft_atoi(root->cmd[0])) > STDERR_FILENO)
			{
				ft_dprintf(STDERR_FILENO, "shell: %d: bad file descriptor\n",
						open_fd);
				return (-1);
			}
			else
				return (open_fd);
		}
	}
	return (exec_redin_get_path(root));
}

int			exec_redin(t_tree *root)
{
	int		ret;
	int		fd[2];

	if (root->types == L_AND && root->cmd[0][0] == '-')
	{
		close(ft_atoi(root->cmd[1]));
		return (sh_interpret(root->right));
	}
	if ((fd[0] = exec_redin_l_and(root)) < 0)
		return (1);
	fd[1] = ft_atoi(root->cmd[1]);
	dup2(fd[0], fd[1]);
	ret = sh_interpret(root->right);
	close(fd[0]);
	return (ret);
}
