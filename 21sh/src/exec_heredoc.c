/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 12:30:09 by cbaldy            #+#    #+#             */
/*   Updated: 2016/05/02 12:33:39 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			exec_heredoc(t_tree *root)
{
	if (g_local->le_mode == 1)
	{
		sh_reset_std_fd();
		ft_dprintf(STDERR_FILENO, "shell: no heredoc with this mode\n");
		exec_free_root(root->right);
		return (1);
	}
	return (heredoc_main(root));
}
