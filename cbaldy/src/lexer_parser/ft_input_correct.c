/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_correct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 10:20:52 by tsanzey           #+#    #+#             */
/*   Updated: 2016/03/30 12:14:54 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		ft_command_isvalid(t_token *tok)
{
	// printf("cmd-> %s, type %d\n", tok->content, tok->type);
	if (tok->type == WORDS || tok->type == SEMICOL
		|| tok->type == AMPERSAND || tok->type == FILENAME
		|| tok->type == COMMANDS)
	{
		if (tok->next)
			return (ft_command_isvalid(tok->next));
		else
			return (1);
	}
	else if (g_f[tok->type](tok))
	{
		if (tok->next)
			return (ft_command_isvalid(tok->next));
		else
			return (1);
	}
	else
	{
		parse_error(tok->content);
		return (0);
	}
}
