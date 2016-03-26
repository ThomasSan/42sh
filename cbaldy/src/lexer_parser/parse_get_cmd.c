/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_get_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/26 15:28:36 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/26 19:44:27 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_build_list.h"

static int	parse_count_words(t_token *tok)
{
	int		i[3];

	i[0] = 0;
	i[1] = 0;
	while (tok != NULL && tok->type == WORDS)
	{
		i[0]++;
		tok = tok->next;
	}
	if (tok != NULL && tok->type == NUMBERS)
		i[1]++;
	if (tok != NULL && tok->type > BACK_QUOTES && tok->type < PIPE)
		i[1] += 2;
	i[2] = i[1];
	while (tok != NULL && (i[2] > 0 || tok->type == WORDS))
	{
		i[0]++;
		tok = tok->next;
		i[2]--;
	}
	return (i[0] - i[1]);
}

int			parse_get_cmd(t_parse **head, t_token *tok)
{
	int		i;
	int		k[2];
	char	**arg;

	i = parse_count_words(tok);
	//printf("i: %d\n", i);
	if ((arg = (char **)malloc(sizeof(char *) * (i + 1))) == NULL)
		return (-1);
	k[0] = 0;
	k[1] = 0;
	while (k[0] < i && tok != NULL)
	{
		if (tok->type == WORDS)
		{
			arg[k[0]] = ft_strdup(tok->content);
			k[0]++;
		}
		else if (tok != NULL && (tok->type == NUMBERS || (tok->type >
						BACK_QUOTES && tok->type < PIPE)))
			i += parse_get_redir(head, tok);
		tok = tok->next;
	}
	arg[k[0]] = NULL;
	return (parse_list_pushback(parse_list_new(arg, CMD), head) + i);
}
