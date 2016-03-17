/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_grammar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 11:05:12 by tsanzey           #+#    #+#             */
/*   Updated: 2016/03/03 11:05:14 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"

int		ft_check_closing(t_token *tok, t_sym sym)
{
	while (tok)
	{
		if (tok->type == sym)
			return (1);
		tok = tok->next;
	}
	return (0);
}

void	pop_token(t_token *tmp, t_token *tok)
{
	while (tmp != tok && tmp)
	{
		tmp->used = 1;
		tmp = tmp->next;
	}
		tmp->used = 1;
}

char	*join_till_closing(t_token *tok, t_sym sym)
{
	char	*str;
	char	*str_tmp;
	t_token	*tmp;

	tmp = tok;
	while (tok->type != sym && tok)
		tok = tok->next;
	str = ft_strdup(tok->content);
	tok = tok->next;
	while (tok->type != sym && tok)
	{
		str_tmp = str;
		str = ft_strjoin(str, tok->content);
		free(str_tmp);
		tok = tok->next;
	}
	str_tmp = str;
	str = ft_strjoin(str, tok->content);
	free(str_tmp);
	pop_token(tmp, tok);
	return (str);
}

char	*option_open_quotes(t_token *tok)
{
	char	*str;
	char	*str_tmp;
	t_token	*tmp;

	str = ft_strdup(tok->content);
	tmp = tok;
	tok = tok->next;
	// pop_token(tmp);
	while (tok)
	{
		str_tmp = str;
		str = ft_strjoin(str, tok->content);
		free(str_tmp);
		tok = tok->next;
	}
	return (str);
}

char	*rules_for_strings(t_token *tok)
{
	char	*str;
	char	*tmp;
	t_sym	sym;

	sym = check_next_token(tok);
	str = ft_strdup(tok->content);
	if (sym == QUOTES || sym == SINGLE_QUOTES)
	{
		tmp = str;
		if (tok->next->next && ft_check_closing(tok->next->next, sym))
			str = ft_strjoin(str, join_till_closing(tok->next, sym));
		else
		{
			printf("next->next = NULL or there is no closing\n");
			str = ft_strjoin(str, option_open_quotes(tok));
			//lancer option open quotes
		}
		free(tmp);
	}
	return (str);
}

char	*rules_for_semicol(char *s)
{
	char	*str;

	str = ft_strdup(s);
	return (str);
}
