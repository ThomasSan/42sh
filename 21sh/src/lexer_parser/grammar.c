/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_grammar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 11:05:12 by tsanzey           #+#    #+#             */
/*   Updated: 2016/04/26 14:48:14 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		rules_for_minus(t_token *tok)
{
	t_sym prev;

	prev = check_prev_token(tok);
	if (prev == DOUBLE_L || prev == LESS_AND
		|| prev == GREAT_AND)
		return (1);
	tok->type = WORDS;
	return (1);
}

int		rules_for_orandif(t_token *tok)
{
	t_sym prev;
	t_sym next;

	prev = check_prev_token(tok);
	next = check_next_token(tok);
	if (((prev == WORDS || prev == FILENAME) && (next == WORDS ||
					next == FILENAME))
		|| (prev == BACK_QUOTES && next == BACK_QUOTES))
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
		prev == AND_GREAT || next == LESS_AND)
		return (1);
	tok->type = WORDS;
	return (1);
}
