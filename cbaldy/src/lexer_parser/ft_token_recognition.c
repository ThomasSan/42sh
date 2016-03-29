/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_recognition.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 15:12:24 by tsanzey           #+#    #+#             */
/*   Updated: 2016/03/29 17:27:56 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parse_build_list.h"

t_token		*pop_middle_token(t_token *tok)
{
	t_token *tmp;

	if (tok->prev)
	{
		tok->prev->next = tok->next;
		if (tok->next)
			tok->next->prev = tok->prev;
	}
	free(tok->content);
	free(tok);
	tmp = tok->next;
	tok = NULL;
	return (tmp);
}

t_token		*join_quoted(t_token *tok)
{
	t_token	*tmp;
	t_token	*tmp1;
	char	*str;

	tmp = tok;
	while (tmp)
	{
		if (tmp->type == QUOTES)
		{
			tmp = tmp->next;
			tmp1 = tmp;
			tmp = tmp->next;
			while (tmp && tmp->type == WORDS)
			{
				str = tmp1->content;
				tmp1->content = ft_strjoin(tmp1->content, tmp->content);
				tmp = pop_middle_token(tmp);
				free(str);
			}
		}
		tmp = tmp->next;
	}
	return (tok);
}

void		return_type_quoted(t_token *tok)
{
	int	is_quoted;

	is_quoted = 0;
	while (tok)
	{
		if (tok->type == QUOTES)
			is_quoted = is_quoted == 1 ? 0 : 1;
		if (is_quoted && tok->type != QUOTES)
			tok->type = WORDS;
		if (tok->type == BACKSLASH)
		{
			if (check_next_token(tok) != WORDS)
			{
				pop_middle_token(tok);
				tok->next->type = WORDS;
			}
		}
		tok = tok->next;
	}
}

t_token		*check_minus(t_token *tok)
{
	t_token	*tmp;
	char	*tmp1;

	tmp = tok;
	while (tmp->next)
	{
		if (tmp->type == MINUS && check_next_token(tmp) == WORDS)
		{
			tmp1 = tmp->next->content;
			tmp->next->content = ft_strjoin(tmp->content, tmp->next->content);
			tmp->type = WORDS;
			free(tmp1);
			if (tmp == tok)
				tok = tok->next;
			tmp = pop_middle_token(tmp);
		}
		else
			tmp = tmp->next;
	}
	return (tok);
}

t_parse		*ft_checking_syntax(t_token *tok)
{
	tok = check_dollar(tok);
	return_type_quoted(tok);
	tok = join_quoted(tok);
	tok = check_minus(tok);
	tok = ft_tild_expand(tok);
	ft_edit_useless(tok);
	tok = ft_token_removal(tok, WHITESPACE);
	tok = ft_token_removal(tok, QUOTES);
	//ft_display_tokens(tok);
	if (!(ft_command_isvalid(tok)))
		return (NULL);
	return (parse_build_list(tok));
	ft_display_tokens(tok);
}
