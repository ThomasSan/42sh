/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 11:37:07 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/22 13:04:03 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree_build_cmd.h"

t_tree		*tree_new_elem(char **cmd, int type)
{
	t_tree	*new;
	if ((new = (t_tree *)malloc(sizeof(t_tree))) == NULL)
		return (NULL);
	new->cmd = cmd;
	new->types = type;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

int			tree_place_type_pipe(t_tree *new, t_tree **root)
{
	t_tree	*tmp;

	tmp = *root;
	if (tmp->types == 8)
		tmp = tmp->right;
	else
	{
		tmp = *root;
		*root = new;
		new->left = tmp;
	}
	return (0);
}

int			tree_place_cmd(t_tree *new, t_tree **root)
{
	t_tree	*tmp;

	if (*root == NULL)
	{
		*root = new;
		return (0);
	}
	tmp = *root;
	while (tmp->right != NULL)
		tmp = tmp->right;
	tmp->right = new;
	return (0);
}
