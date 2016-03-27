/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 11:37:07 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/27 18:33:39 by cbaldy           ###   ########.fr       */
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
	if (tmp->types == END)
	{
		tmp = tmp->right;
		(*root)->right = new;
		new->left = tmp;
	}
	else
	{
		tmp = *root;
		*root = new;
		new->left = tmp;
	}
	return (0);
}

int			tree_place_type_red(t_tree *new, t_tree **root)
{
	t_tree	*tmp;
	t_tree	*tmp2;
	
	if ((*root)->right == NULL)
	{
		tmp = *root;
		*root = new;
		new->left = tmp;
	}
	else
	{
		tmp = *root;
		while (tmp->right != NULL && tmp->right->types != CMD)
			tmp = tmp->right;
		tmp2 = tmp->right;
		tmp->right = new;
		new->left = tmp2;
	}
	return (0);
}

int			tree_place_cmd(t_tree *new, t_tree **root)
{
	t_tree	*tmp;

	tmp = *root;
	while (tmp->right != NULL)
		tmp = tmp->right;
	if (tmp->types == CMD)
		return (-1);
	else if (tmp->types < TUBES)
		tmp->left = new;
	else
		tmp->right = new;
	return (0);
}

int			tree_place_type_end(t_tree *new, t_tree **root)
{
	t_tree	*tmp;

	tmp = *root;
	*root = new;
	new->left = tmp;
	return (0);
}
