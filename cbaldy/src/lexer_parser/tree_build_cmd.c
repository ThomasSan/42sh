/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_build_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 10:22:10 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/27 19:11:09 by cbaldy           ###   ########.fr       */
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
	{
		printf("left\n");
		tree_print(root->left);
	}
	if (root->right != NULL)
	{
		printf("right\n");
		tree_print(root->right);
	}
	printf("up\n");
	return (0);
}

int			tree_place_bq(t_tree *new, t_tree **root)
{
	t_tree *tmp;
	t_tree *tmp1;

	tmp = *root;
	if (tmp->types >= TUBES && tmp->types <= OR_IF)
	{
		tmp1 = tmp->right;
		new->right = tmp1;
		tmp->right = new;
	}
	else
	{
		new->right = tmp;
		*root = new;
	}
	return (0);
}

static int	tree_insert_elem(t_tree *new, t_tree **root)
{
	if (*root == NULL)
	{
		*root = new;
		return (0);
	}
	else if (new->types == CMD)
		return (tree_place_cmd(new, root));
	else if (new->types < TUBES)
		return (tree_place_type_red(new, root));
	else if (new->types < END)
		return (tree_place_type_pipe(new, root));
	else if (new->types == B_QUOTES)
		return (tree_place_bq(new, root));
	else
		return (tree_place_type_end(new, root));
}

t_tree		*tree_build_cmd(t_parse *head)
{
	t_tree	*root;
	t_tree	*new;
	t_parse	*tmp;
	int		bq;

	root = NULL;
	bq = 0;
	while (head != NULL)
	{
		if (bq == 0 || head->type != B_QUOTES)
		{
			if (head->type == B_QUOTES)
				bq = bq == 0 ? 1 : 0;
			if ((new = tree_new_elem(head->arg, head->type)) == NULL)
				return (NULL);
			if (tree_insert_elem(new, &root) < 0)
				return (NULL);
		}
		tmp = head;
		head = head->next;
		free(tmp);
	}
	tree_print(root);
	return (root);
}
