/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_get_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/26 15:28:36 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/27 17:55:41 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_build_list.h"

static int	parse_count_words(t_token *tok)
{
	int		i;

	i = 0;
	while (tok != NULL && tok->type == WORDS)
	{
		i++;
		tok = tok->next;
	}
	return (i);
}

static char	**parse_cpy_arg(t_parse *com, int len)
{
	char	**new_arg;
	int		i;
	
	if ((new_arg = (char **)malloc(sizeof(char *) * (len + 1))) == NULL)
		return (NULL);
	i = 0;
	while (com->arg[i] != NULL)
	{
		new_arg[i] = com->arg[i];
		i++;
	}
	return (new_arg);
}

static int	parse_insert_words(t_parse *com, t_token *tok)
{
	int		i[2];
	char	**new_arg;

	i[0] = 0;
	while (com->arg[i[0]] != NULL)
		i[0]++;
	i[1] = parse_count_words(tok);
	if ((new_arg = parse_cpy_arg(com, i[0] + i[1])) == NULL)
		return (-1);
	while (tok != NULL && tok->type == WORDS)
	{
		new_arg[i[0]] = ft_strdup(tok->content);
		i[0]++;
		tok = tok->next;
	}
	new_arg[i[0]] = NULL;
	free(com->arg);
	com->arg = new_arg;
	return (i[1]);
}

static int	parse_concat_cmd(t_parse **head, t_token *tok)
{
	t_parse	*tmp[2];

	tmp[0] = *head;
	tmp[1] = NULL;
	if (tmp[0] == NULL)
		return (-1);
	while ((tmp[0])->next != NULL)
	{
		tmp[1] = tmp[0];
		tmp[0] = tmp[0]->next;
	}
	if ((tmp[0])->type > CMD && (tmp[0])->type < TUBES && tmp[1] != NULL
			&& (tmp[1])->type == CMD)
		return (parse_insert_words(tmp[1], tok));
	return (-1);
}

int			parse_get_cmd(t_parse **head, t_token *tok)
{
	int		i;
	char	**arg;

	if ((i = parse_concat_cmd(head, tok)) > 0)
		return (i);
	i = parse_count_words(tok);
	if ((arg = (char **)malloc(sizeof(char *) * (i + 1))) == NULL)
		return (-1);
	i = 0;
	while (tok != NULL && tok->type == WORDS)
	{
		arg[i] = ft_strdup(tok->content);
		i++;
		tok = tok->next;
	}
	arg[i] = NULL;
	return (parse_list_pushback(parse_list_new(arg, CMD), head) + i);
}
