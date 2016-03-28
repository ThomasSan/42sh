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
	if (check_next_token(tok) == WORDS)
	{
		tok->next->type = FILENAME;
		return (1);
	}
	return (0);
}

int			rules_for_less(t_token *tok)
{
	if (check_next_token(tok) == WORDS)
	{
		tok->next->type = FILENAME;
		return (1);
	}
	return (0);
}

int			rules_for_great_and(t_token *tok)
{
	if (check_next_token(tok) == WORDS || check_next_token(tok) == MINUS
		|| check_next_token(tok) == NUMBERS)
		return (1);
	return (0);
}

int			rules_for_less_and(t_token *tok)
{
	if (check_next_token(tok) == MINUS || check_next_token(tok) == NUMBERS)
		return (1);
	return (0);
}

int			rules_for_and_great(t_token *tok)
{
	if (check_next_token(tok) == WORDS)
		return (1);
	return (0);
}
