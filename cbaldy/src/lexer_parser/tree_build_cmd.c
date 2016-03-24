/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_build_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 10:22:10 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/23 11:00:37 by cbaldy           ###   ########.fr       */
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

static int	tree_get_cmd(t_token *tok, t_tree **root)
{
	int		i[2];
	t_token	*tmp;
	char	**str;
	t_tree	*new;

	i[0] = 0;
	tmp = tok;
	while (tmp != NULL && tmp->type == -1)
	{
		tmp = tmp->next;
		i[0]++;
	}
	if ((str = (char **)malloc(sizeof(char *) * (i[0] + 1))) == NULL)
		return (i[0]);
	i[1] = 0;
	while (i[1] < i[0])
	{
		str[i[1]] = ft_strdup(tok->content);
		tok = tok->next;
		i[1]++;
	}
	str[i[1]] = NULL;
	if ((new = tree_new_elem(str, 0)) == NULL)
		return (i[0]);
	tree_place_cmd(new, root);
	return (i[0]);
}

static int	tree_get_other(t_token *tok, t_tree **root)
{
	t_tree	*new;

	if (tok->type == 7)
	{
		if ((new = tree_new_elem(NULL, 5)) == NULL)
			return (1);
		tree_place_type_pipe(new, root);
		return (1);
	}
	if (tok->type == 3)
	{
		if ((new = tree_new_elem(&(tok->next->content), 2)) == NULL)
			return (2);
		tree_place_type_red(new, root);
		return (2);
	}
	return (1);
}

t_tree		*tree_build_cmd(t_token *tok)
{
	t_tree	*root;
	//t_token *tmp; a rajouter pour free;
	int		i;

	root = NULL;
	i = 0;
	while (tok != NULL)
	{
		if (tok->type == -1)
			i = tree_get_cmd(tok, &root);
		else
			i = tree_get_other(tok, &root);
		while (i > 0 && tok != NULL)
		{
			tok = tok->next;
			i--;
		}
	}
	tree_print(root);
	//free_token_list(tmp);
	return (root);
}
