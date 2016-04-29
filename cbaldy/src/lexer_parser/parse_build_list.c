/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_build_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/26 15:13:17 by cbaldy            #+#    #+#             */
/*   Updated: 2016/04/29 12:18:13 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_build_list.h"
#include "ft_printf.h"

/*int			parse_print(t_parse *head)
{
	int		i;

	while (head != NULL)
	{
		i = 0;
		ft_printf("command: ");
		while (head->arg != NULL && head->arg[i] != NULL)
		{
			ft_printf("%s\n", head->arg[i]);
			i++;
		}
		ft_printf("type: %d\n", head->type);
		head = head->next;
	}
	return (0);
}*/

static int	parse_get_pipe_type(t_parse **head, t_token *tok)
{
	int		op;

	if (tok->type == PIPE)
		op = TUBES;
	else if (tok->type == SEMICOL)
		op = END;
	else if (tok->type == D_PIPE)
		op = OR_IF;
	else
		op = AND_IF;
	return (parse_list_pushback(parse_list_new(NULL, op), head) + 1);
}

static int	parse_get_subshell(t_parse **head, t_token *tok)
{
	char	**arg;

	if ((arg = (char **)malloc(sizeof(char *) * 2)) == NULL)
		return (1);
	arg[0] = ft_strdup(tok->content);
	arg[1] = NULL;
	return (parse_list_pushback(parse_list_new(arg, S_SHELL), head) + 1);
}

static int	parse_analyse_token(t_parse **head, t_token *tok)
{
	if (tok->type == WORDS)
		return (parse_get_cmd(head, tok));
	else if (tok->type == SUBSHELL)
		return (parse_get_subshell(head, tok));
	else if ((tok->type >= DIPLE_R && tok->type <= DOUBLE_L) ||
			tok->type == NUMBERS || (tok->type >= LESS_AND && tok->type
				<= AND_GREAT))
		return (parse_get_redir(head, tok));
	else if (tok->type == PIPE || tok->type == SEMICOL ||
		tok->type == D_PIPE || tok->type == D_SAND)
		return (parse_get_pipe_type(head, tok));
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
	return (head);
}
