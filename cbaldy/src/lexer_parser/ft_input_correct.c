/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_correct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 10:20:52 by tsanzey           #+#    #+#             */
/*   Updated: 2016/04/25 12:34:15 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "ft_printf.h"

int		ft_command_isvalid(t_token *tok)
{
	if (tok->type == WORDS || tok->type == AMPERSAND
		|| tok->type == FILENAME || tok->type == BACK_QUOTES
		|| tok->type == SUBSHELL)
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

int		rules_for_par(t_token *tok)
{
	(void)tok;
	return (0);
}

int		rules_for_semicol(t_token *tok)
{
	if (check_next_token(tok) == SEMICOL || check_prev_token(tok) == SEMICOL)
		return (0);
	return (1);
}