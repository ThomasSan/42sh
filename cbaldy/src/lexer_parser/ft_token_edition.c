/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_edition.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 15:23:00 by tsanzey           #+#    #+#             */
/*   Updated: 2016/03/30 12:11:33 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int			is_word_or(char *s, int i)
{
	if (!ft_isdigit(s[i]))
		return (0);
	if (s[i + 1] != '\0' && (s[i + 1] == '>' || s[i + 1] == '<'))
		return (1);
	if (s[i - 1] && s[i - 1] == '&')
		return (1);
	if (s[i + 1] != '\0' && ft_isdigit(s[i + 1]))
		return (1);
	if (s[i - 1] != '\0' && ft_isdigit(s[i - 1]))
		return (1);
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
		printf("t : %s, type : %d\n", tok->content, tok->type);
		tok = tok->next;
	}
}

int			ft_edit_useless(t_token *tok)
{
	while (tok)
	{
		if (tok->type == DOLLAR)
			tok->type = WORDS;
		tok = tok->next;
	}
	return (1);
}
