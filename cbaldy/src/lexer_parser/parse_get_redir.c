/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_get_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/26 17:47:51 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/26 19:41:28 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_build_list.h"

static int	parse_get_redout(t_parse **head, t_token *tok)
{
	char	**arg;
	char	*std;
	int		i;

	i = 0;
	std = "1";
	if (tok != NULL && (tok->type == DIPLE_L || tok->type == DOUBLE_L))
	{
		i++;
		std = "0";
	}
	if ((arg = (char **)malloc(sizeof(char *) * 3)) == NULL)
		return (0);
	if (tok->prev->type == NUMBERS)
		arg[i] = ft_strdup(tok->prev->content);
	else
		arg[i] = ft_strdup(std);
	arg[1 - i] = ft_strdup(tok->next->content);
	arg[2] = NULL;
	return (parse_list_pushback(parse_list_new(arg, tok->type - 2), head));
}

int			parse_get_redir(t_parse **head, t_token *tok)
{
	int		i;

	i = 0;
	if (tok->type == NUMBERS)
	{
		tok = tok->next;
		i++;
	}
	parse_get_redout(head, tok);
	if (tok->type > BACK_QUOTES && tok->type < PIPE)
	{
		tok = tok->next->next;
		i++;
	}
	while (tok != NULL && tok->type == WORDS)
	{
		tok = tok->next->next;
		i++;
	}
	return (i);
}
