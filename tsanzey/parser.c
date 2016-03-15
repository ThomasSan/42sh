/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 11:06:02 by tsanzey           #+#    #+#             */
/*   Updated: 2016/03/03 11:06:04 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"

char	*parsing_nodes(t_token *tok)
{
	char	*str;

	str = NULL;
	if (tok->type == -1)
	{
		str = rules_for_strings(tok);
	}
	else
	{
		str = rules_for_semicol(tok->content);
	}
	return (str);
}

int		ft_get_types(t_token *tok)
{
	if (tok->type <= 2)
		return (0);
	if (tok->type == DIPLE_R)
		return (1);
	if (tok->type == DIPLE_L)
		return (2);
	if (tok->type == PIPE)
		return (3);
	if (tok->type == DOUBLE_R)
		return (4);
	if (tok->type == DOUBLE_L)
		return (5);
	if (tok->type == SEMICOL)
		return (6);
	return (0);
}

t_tree	**ft_push_node(t_tree **head, char *str, t_token *tok)
{
	t_tree	*new;
	t_tree	*tmp;

	if (!(new = (t_tree*)malloc(sizeof(t_tree))))
		return (NULL);
	new->types = ft_get_types(tok);
	new->content = ft_strdup(str);
	free(str);
	new->next = NULL;
	new->prev = NULL;
	if (*head)
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	else
		*head = new;
	return (head);
}

t_tree	*tree_generator(t_tree *head, t_token *tok)
{
	char	*str;

	str = NULL;
	head = NULL;
	while (tok)
	{
		if (tok->used == 0)
		{
			str = parsing_nodes(tok);
			// printf("s : %s, used %d, tok %s\n", str, tok->used, tok->content);
			tok->used = 1;
			head = *ft_push_node(&head, str, tok);
		}
		tok = tok->next;
	}
	return (head);
}
