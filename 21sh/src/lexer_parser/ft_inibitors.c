/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inibitors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 12:43:18 by tsanzey           #+#    #+#             */
/*   Updated: 2016/05/02 18:43:17 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "ft_printf.h"

int			isinibed(t_token *tok)
{
	int		next;

	next = check_next_token(tok);
	if (next == QUOTES)
		return (1);
	if (next == DOLLAR)
		return (1);
	if (next == BACK_QUOTES)
		return (1);
	if (next == BACKSLASH)
		return (1);
	return (0);
}

t_token		*join_tokens(t_token *tok)
{
	t_token *tmp;
	char	*str;

	tmp = tok;
	while (tok)
	{
		if (tok->next && tok->type == WORDS && check_next_token(tok) == WORDS)
		{
			str = tok->content;
			tok->content = ft_strjoin(tok->content, tok->next->content);
			free(str);
			pop_middle_token(tok->next);
		}
		else
			tok = tok->next;
	}
	return (tmp);
}

t_token		*inibitor_handler(t_token *tok)
{
	t_token *tmp;
	int		inib;

	tmp = tok;
	inib = 0;
	while (tok)
	{
		if (tok->type == SINGLE_QUOTES || tok->type == QUOTES)
			inib = inib == 0 ? 1 : 0;
		if (tok->type == BACKSLASH && inib == 0)
		{
			if (tok->next && check_next_token(tok) != WORDS)
				tok->next->type = WORDS;
			if (tmp == tok)
				tmp = tmp->next;
			tok = pop_middle_token(tok);
		}
		else
			tok = tok->next;
	}
	return (tmp);
}

int			find_closing(char *s, int i)
{
	while (s[i++])
	{
		if (s[i] == '`')
			return (1);
	}
	return (0);
}
