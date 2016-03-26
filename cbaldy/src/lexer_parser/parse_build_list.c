/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_build_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/26 15:13:17 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/26 19:23:54 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_build_list.h"

int	parse_print(t_parse *head)
{
	int		i;

	while (head != NULL)
	{
		i = 0;
		while (i < 2 && head->arg[i] != NULL)
		{
			printf("%s ", head->arg[i]);
			i++;
		}
		printf("%d\n", head->type);
		head = head->next;
	}
	return (0);
}

static int	parse_analyse_token(t_parse **head, t_token *tok)
{
	if (tok->type == WORDS)
		return (parse_get_cmd(head, tok));
	//else if (tok->type == PIPE || tok->type == SEMICOL ||
	//	tok->type == D_PIPE || tok->type == D_SAND)
	//	head = ft_push_pipe(head, tok);
	else if ((tok->type > BACK_QUOTES && tok->type < PIPE)
			|| tok->type == NUMBERS)
		return (parse_get_redir(head, tok));
	//else if (tok->type == DIPLE_R || tok->type == DOUBLE_R)
	//	head = ft_push_output(head, tok);
	return (1);
}

t_parse		*parse_build_list(t_token *tok)
{
	t_parse *head;
	t_token	*tmp;
	int		i;

	head = NULL;
	while (tok)
	{
		if ((i = parse_analyse_token(&head, tok)) < 0)
			return (NULL);
		//printf("ret: %d\n", i);
		while (i > 0)
		{
			tmp = tok;
			tok = tok->next;
			if (tmp->content != NULL)
				free(tmp->content);
			free(tmp);
			i--;
		}
	}
	parse_print(head);
	return (head);
}
