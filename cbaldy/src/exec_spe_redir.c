/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_spe_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 11:59:03 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/28 13:16:09 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		exec_spe_redir(t_tree *root)
{
	if (root->types == AND_G)
	{
		ft_putendl("ok");
		return (exec_redout(root));
	}
	return (0);
}
