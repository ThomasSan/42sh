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
	if (check_next_token(tok) == WORDS &&
		(check_prev_token(tok) == WORDS || check_prev_token(tok) == FILENAME))
		return (1);
	return (0);
}
