/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_grammar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 11:05:12 by tsanzey           #+#    #+#             */
/*   Updated: 2016/03/28 15:17:23 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		rules_for_minus(t_token *tok)
{
	if (check_prev_token(tok) == DOUBLE_L || check_prev_token(tok) == LESS_AND
		|| check_prev_token(tok) == GREAT_AND)
		return (1);
	tok->type = WORDS;
	return (1);
}

int		rules_for_orandif(t_token *tok)
{
	if (check_prev_token(tok) == WORDS && check_next_token(tok) == WORDS)
		return (1);
	return (0);
}

int		rules_for_numbers(t_token *tok)
{
	t_sym next;
	t_sym prev;

	next = check_next_token(tok);
	prev = check_prev_token(tok);
	if (next == DIPLE_R || next == DOUBLE_R || next == GREAT_AND ||
		prev == AND_GREAT)
		return (1);
	tok->type = WORDS;
	return (1);
}