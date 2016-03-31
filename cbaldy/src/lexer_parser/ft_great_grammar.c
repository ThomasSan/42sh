/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_great_grammar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 15:20:11 by tsanzey           #+#    #+#             */
/*   Updated: 2016/03/28 15:20:13 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int			rules_for_great(t_token *tok)
{
	t_sym sym;

	sym = check_next_token(tok);
	if (sym == WORDS)
	{
		tok->next->type = FILENAME;
		return (1);
	}
	if (sym == COMMANDS)
		return (1);
	return (0);
}

int			rules_for_less(t_token *tok)
{
	t_sym sym;

	sym = check_next_token(tok);
	if (sym == WORDS)
	{
		tok->next->type = FILENAME;
		return (1);
	}
	if (sym == COMMANDS)
		return (1);
	return (0);
}

int			rules_for_great_and(t_token *tok)
{
	t_sym sym;

	sym = check_next_token(tok);
	if (sym == WORDS || sym == MINUS
		|| sym == NUMBERS || sym == COMMANDS)
		return (1);
	return (0);
}

int			rules_for_less_and(t_token *tok)
{
	t_sym sym;

	sym = check_next_token(tok);
	if (sym == MINUS || sym == NUMBERS)
		return (1);
	return (0);
}

int			rules_for_and_great(t_token *tok)
{
	t_sym sym;

	sym = check_next_token(tok);
	if (sym == WORDS || sym == COMMANDS)
		return (1);
	return (0);
}
