/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_build_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 12:51:45 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/21 13:05:07 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_hash_tree	*hash_new_elem(char *name, char *path)
{
	t_hash_tree	*new;

	if ((new = (t_hash_tree *)malloc(sizeof(t_hash_tree))) == NULL)
		return (NULL);
	new->name = ft_strdup(name);
	new->path = ft_strdup(path);
	new->left = NULL;
	new->right = NULL;
	new->root = NULL;
	return (new);
}

static int			hash_add_elem(t_hash_tree *new, t_hash_tree **root)
{	
	t_hash_tree	*tmp;
	int			i;

	tmp = *root;
	if (tmp == NULL)
	{
		*root = new;
		return (0);
	}
	i = 1;
	while (i != 0)
	{
		if (ft_strcmp(new->name, tmp->name) > 0 && tmp->right != NULL)
			tmp = tmp->right;
		else if (ft_strcmp(new->name, tmp->name) < 0 && tmp->left != NULL)
			tmp = tmp->left;
		else
			i == 0;
	}
	return (0);
}

int					hash_build_tree(char *name, char *path, t_hash_tree **root)
{
	t_hash_tree	*new;
	t_hash_tree	*tmp;

	if ((new = hash_new_elem(name, path)) == NULL)
		return (-1);
	hash_add_elem(new, root);
	return (0);
}
