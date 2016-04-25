/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_preparse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 15:04:31 by tsanzey           #+#    #+#             */
/*   Updated: 2016/04/23 15:49:22 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_parse		*ft_push_pipe(t_parse *head, t_token *tok)
{
	t_parse	*new;
	t_parse	*tmp;

	if (!(new = (t_parse*)malloc(sizeof(t_parse))))
		return (NULL);
	new->arg = NULL;
	if (tok->type == PIPE || tok->type == SEMICOL)
		new->type = tok->type == PIPE ? TUBES : END;
	if (tok->type == D_PIPE || tok->type == D_SAND)
		new->type = tok->type == D_PIPE ? OR_IF : AND_IF;
	new->next = NULL;
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (head);
}

t_parse		*ft_push_redir(t_parse *head)
{
	t_parse	*new;
	t_parse	*tmp;

	if (!(new = (t_parse*)malloc(sizeof(t_parse))))
		return (NULL);
	new->arg = NULL;
	new->type = TUBES;
	new->next = NULL;
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (head);
}

t_parse		*ft_analyse_token(t_parse *head, t_token *tok)
{
	if (tok->type == PIPE || tok->type == SEMICOL ||
		tok->type == D_PIPE || tok->type == D_SAND)
		head = ft_push_pipe(head, tok);
	if (tok->type == DIPLE_L || tok->type == DOUBLE_L)
		head = ft_push_input(head, tok);
	if (tok->type == DIPLE_R || tok->type == DOUBLE_R)
		head = ft_push_output(head, tok);
	return (head);
}

t_parse		*ft_parse_cmd(t_parse *head, t_token *tok)
{
	t_parse	*new;
	t_parse	*tmp;

	if (!(new = (t_parse*)malloc(sizeof(t_parse))))
		return (NULL);
	new = ft_push_in_tab(new, tok);
	new->next = NULL;
	new->type = CMD;
	if (!head)
		head = new;
	else
	{
		tmp = head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (head);
}

t_parse		*sh_preparse(t_token *tok)
{
	t_parse *head;

	head = NULL;
	while (tok)
	{
		if (tok->type == WORDS)
		{
			head = ft_parse_cmd(head, tok);
			while (tok && tok->type == WORDS)
				tok = tok->next;
		}
		else if (tok->type == NUMBERS || tok->type == FILENAME)
			tok = tok->next;
		else
		{
			head = ft_analyse_token(head, tok);
			tok = tok->next;
		}
	}
	return (head);
}
