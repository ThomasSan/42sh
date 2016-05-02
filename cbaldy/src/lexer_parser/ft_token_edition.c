/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_edition.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 15:23:00 by tsanzey           #+#    #+#             */
/*   Updated: 2016/04/25 12:35:08 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "shell.h"
#include "ft_printf.h"

int			is_word_or(char *s, int i)
{
	int		j;

	if (!ft_isdigit(s[i]))
		return (0);
	if (s[i + 1] != '\0' && (s[i + 1] == '>' || s[i + 1] == '<'))
		return (1);
	if (s[i - 1] && s[i - 1] == '&')
		return (1);
	if (s[i + 1] != '\0' && ft_isdigit(s[i + 1]))
	{
		j = 0;
		while (s[i + j + 1] && ft_isdigit(s[i + j + 1]))
			j++;
		if (s[i + 1] != '\0' && (s[i + 1] == '>' || s[i + 1] == '<'))
			return (1);
	}
	if (s[i - 1] != '\0' && ft_isdigit(s[i - 1]))
	{
		j = 0;
		while ((i + j) > 0 && ft_isdigit(s[i + j]))
			j--;
		if (s[i + j] && s[i + j] == '&')
			return (1);
	}
	return (0);
}

int			ft_next_token(char *s, int start, int type)
{
	int i;

	i = 0;
	while (s[start + i] && ft_token_type(s, start + i) == type)
		i++;
	return (start + i);
}

t_token		*ft_token_removal(t_token *tok, t_sym sym)
{
	t_token *tmp;
	int		i;

	i = 0;
	tmp = tok;
	while (tmp)
	{
		i++;
		if (tmp->type == sym)
		{
			if (tok == tmp)
				tok = tok->next;
			if (check_next_token(tmp) == sym && sym != WHITESPACE)
				tmp->next = ft_emptyquotes(tmp->next);
			tmp = pop_middle_token(tmp);
		}
		else
			tmp = tmp->next;
	}
	return (tok);
}

void		ft_display_tokens(t_token *tok)
{
	while (tok)
	{
		ft_printf("t : %s, type : %d add: %p\n", tok->content, tok->type, tok);
		tok = tok->next;
	}
}

int			ft_edit_useless(t_token *tok)
{
	t_token	*tmp;

	tmp = tok;
	while (tmp)
	{
		if (tmp->type == DOLLAR)
			tmp->type = WORDS;
		if (tmp->type == O_PAR || tmp->type == C_PAR)
		{
			if (tok == tmp)
				tok = tok->next;
			tmp = pop_middle_token(tmp);
		}
		else
		tmp = tmp->next;
	}
	return (1);
}
