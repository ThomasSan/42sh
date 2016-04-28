/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_build_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 10:22:10 by cbaldy            #+#    #+#             */
/*   Updated: 2016/04/28 15:45:34 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree_build_cmd.h"
#include "shell.h"

/*static int	tree_print(t_tree *root)
{
	int		i;

	if (root == NULL)
	{
		ft_putendl("NULL ROOT");
		return (0);
	}
	ft_printf("type: %d  ", root->types);
	if (root->types == 0)
	{
		i = 0;
		while (root->cmd[i] != NULL)
		{
			ft_printf("%s", root->cmd[i]);
			i++;
		}
	}
	ft_putchar('\n');
	if (root->left != NULL)
	{
		tree_print(root->left);
	}
	if (root->right != NULL)
	{
		tree_print(root->right);
	}
	return (0);
}*/

static int	tree_place_sshell(t_tree *new, t_tree **root)
{
	t_tree *leg;

	if ((leg = sh_lexer_parser(new->cmd[0])) == NULL)
		return (-1);
	new->right = leg;
	ft_free_tab(new->cmd);
	new->cmd = NULL;
	if (*root == NULL)
	{
		*root = new;
		return (0);
	}
	return (tree_place_cmd(new, root));
}

static int	tree_insert_elem(t_tree *new, t_tree **root)
{
	if (new->types == S_SHELL)
		return (tree_place_sshell(new, root));
	else if (*root == NULL)
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
		{
			if (new != NULL)
				exec_free_root(new);
			exec_free_root(root);
			parse_list_free(head->next);
			free(head);
			root = NULL;
			break ;
		}
		tmp = head->next;
		free(head);
		head = tmp;
	}
	return (root);
}
