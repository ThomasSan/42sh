/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 16:53:20 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/27 17:00:08 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "lexer.h"
#include "tree_build_cmd.h"

t_token	*free_token_list(t_token *tok)
{
	t_token	*tmp;

	while (tok)
	{
		tmp = tok;
		tok = tok->next;
		free(tmp->content);
		free(tmp);
	}
	return (tok);
}

t_tree		*sh_lexer_parser(char *str)
{
	t_token	*tok;
	t_parse *head;

	tok = NULL;
	head = NULL;
	if ((tok = ft_tokeniser(str, tok)) == NULL)
		return (NULL);
	if ((head = ft_checking_syntax(tok)) == NULL)
		return (NULL);
	return (tree_build_cmd(head));
	/*
	t_parse *tail;
	tail = head;
	 while (tail)
	{
	 	int i = 0;
		printf("type %d\n", tail->type);
 		while (tail->arg[i])
	 	{
	 		printf("arg[%d] %s\n", i, tail->arg[i]);
	 		i++;
	 	}
	 	tail = tail->next;
	 }
	 printf("exit\n");
	 return (NULL);
	 */
}

//Dans cet ordre :
// 1/ tild expansion
// 2/ changer var $""
// 3/ remove spaces
// 4/ remove quotes
