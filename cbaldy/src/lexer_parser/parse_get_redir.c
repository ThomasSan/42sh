/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_get_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/26 17:47:51 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/27 19:00:54 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_build_list.h"

static int	parse_sort_type(int type)
{
	if (type == DIPLE_R)
		return (GREAT);
	else if (type == DOUBLE_R)
		return (D_GREAT);
	else if (type == DIPLE_L)
		return (LESS);
	else if (type == DOUBLE_L)
		return (D_LESS);
	else if (type == LESS_AND)
		return (L_AND);
	else if (type == GREAT_AND)
		return (G_AND);
	else if (type == AND_GREAT)
		return (AND_G);
	else
		return (0);
}

static int	parse_get_redout(t_parse **head, t_token *tok)
{
	char	**arg;
	char	*std;
	int		i[2];

	i[0] = 0;
	i[1] = parse_sort_type(tok->type);
	std = "1";
	if (tok != NULL && (i[1] == LESS || i[1] == D_LESS || i[1] == L_AND))
	{
		i[0]++;
		std = "0";
	}
	if ((arg = (char **)malloc(sizeof(char *) * 3)) == NULL)
		return (0);
	if (tok->prev != NULL && tok->prev->type == NUMBERS)
		arg[i[0]] = ft_strdup(tok->prev->content);
	else
		arg[i[0]] = ft_strdup(std);
	arg[1 - i[0]] = ft_strdup(tok->next->content);
	arg[2] = NULL;
	return (parse_list_pushback(parse_list_new(arg, i[1]), head));
}

int			parse_get_redir(t_parse **head, t_token *tok)
{
	int		i;

	i = 2;
	if (tok->type == NUMBERS)
	{
		tok = tok->next;
		i++;
	}
	return (parse_get_redout(head, tok) + i);
}
