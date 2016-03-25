/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_build_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 10:22:10 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/25 17:47:04 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree_build_cmd.h"

static int	tree_print(t_tree *root)
{
	int		i;

	if (root->types == 0)
	{
		i = 0;
		while (root->cmd[i] != NULL)
		{
			printf("%s ", root->cmd[i]);
			i++;
		}
		printf("\n");
	}
	else
		printf("%d\n", root->types);
	if (root->left != NULL)
		tree_print(root->left);
	if (root->right != NULL)
		tree_print(root->right);
	return (0);
}

static int	tree_insert_elem(t_tree *new, t_tree **root)
{
	if (new->types == CMD)
		return (tree_place_cmd(new, root));
	else if (new->types < TUBES)
		return (tree_place_type_red(new, root));
	else if (new->types < END)
		return (tree_place_type_pipe(new, root));
	else
		return (tree_place_type_end(new, root));
}

t_tree		*tree_build_cmd(t_parse *head)
{
	t_tree	*root;
	t_tree	*new;
	t_parse	*tmp;

	root = NULL;
	while (head != NULL)
	{
		if ((new = tree_new_elem(head->arg, head->type)) == NULL)
			return (NULL);
		if (tree_insert_elem(new, &root) < 0)
			return (NULL);
		tmp = head;
		head = head->next;
		free(tmp);
	}
	//tree_print(root);
	return (root);
	tree_print(root);
}
