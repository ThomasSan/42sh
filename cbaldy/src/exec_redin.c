/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 12:10:32 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/29 12:10:42 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*exec_redin_get_path(t_tree *root)
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

int			exec_redin(t_tree *root)
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
