/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_grammar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 15:11:53 by tsanzey           #+#    #+#             */
/*   Updated: 2016/03/28 15:12:02 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int					rules_for_pipes(t_token *tok)
{
	t_sym prev;
	t_sym next;

	prev = check_prev_token(tok);
	next = check_next_token(tok);
	if ((next == WORDS || next == COMMANDS) &&
		(prev == WORDS || prev == FILENAME || prev == COMMANDS))
		return (1);
	return (0);
}
