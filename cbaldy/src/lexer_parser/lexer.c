/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 11:05:40 by tsanzey           #+#    #+#             */
/*   Updated: 2016/03/25 14:54:04 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		ft_other_redirs(char *s, int i, int type)
{
	static const char	*token_types[] = {"\"", "\'", "`", ">", ">>", "<",
	"<<", "|", ";", "&", "~", "\\", "$", "-", "\0"};

	if (s[i + 1] && type == DIPLE_R && s[i + 1] == s[i])
		return (4);
	if (s[i + 1] && type == DIPLE_L && s[i + 1] == s[i])
		return (6);
	if (s[i + 1] && type == DIPLE_R && s[i + 1] == *token_types[AMPERSAND])
		return (GREAT_AND);
	if (s[i + 1] && type == DIPLE_L && s[i + 1] == *token_types[AMPERSAND])
		return (LESS_AND);
	if (s[i + 1] && type == AMPERSAND && s[i + 1] == *token_types[DIPLE_R])
		return (AND_GREAT);
	if (s[i + 1] && type == AMPERSAND && s[i + 1] == *token_types[AMPERSAND])
		return (D_SAND);
	if (s[i + 1] && type == PIPE && s[i + 1] == *token_types[PIPE])
		return (D_PIPE);
	return (type);
}

int		ft_token_type(char *s, int i)
{
	int					type;
	int					j;
	static const char	*token_types[] = {"\"", "\'", "`", ">", ">>", "<",
	"<<", "|", ";", "&", "~", "\\", "$", "-", "\0"};

	type = WORDS;
	j = 0;
	if (is_word_or(s, i))
		return (NUMBERS);
	if (ft_isspace(s[i]))
		return (WHITESPACE);
	while (*token_types[j])
	{
		if (s[i] == *token_types[j])
		{
			type = j;
			if (j == DIPLE_R || j == DIPLE_L || j == AMPERSAND
				|| j == PIPE)
				return (ft_other_redirs(s, i, type));
			return (type);
		}
		j++;
	}
	return (type);
}

char	*tok_content(char *s, int start, int type)
{
	int					i;
	char				*dst;
	static const char	*token_types[] = {"\"", "\'", "`", ">", ">>", "<",
	"<<", "|", ";", "&", "~", "\\", "$", "-", "<&", ">&", "&>", "||",
	"&&", "\0"};

	if (type == DOUBLE_R || type == DOUBLE_L ||
		(type >= LESS_AND && type <= D_SAND))
	{
		dst = ft_strdup(token_types[type]);
		return (dst);
	}
	i = 0;
	if (type == WORDS)
	{
		while (s[start + i] && ft_token_type(s, start + i) == WORDS)
			i++;
	}
	else if (type == NUMBERS)
		while (s[start + i] && ft_token_type(s, start + i) == NUMBERS)
			i++;
	i = i == 0 ? 1 : i;
	dst = ft_strsub(s, start, i);
	return (dst);
}

t_token	*ft_push_token(t_token *head, t_token *new)
{
	t_token	*tmp;

	new->used = 0;
	new->next = NULL;
	new->prev = NULL;
	if (!head)
		head = new;
	else
	{
		tmp = head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	return (head);
}

t_token	*ft_tokeniser(char *s, t_token *head)
{
	t_token	*new;
	int		i;

	i = 0;
	while (s[i])
	{
		if (!(new = (t_token*)malloc(sizeof(t_token))))
			return (NULL);
		new->type = ft_token_type(s, i);
		new->content = tok_content(s, i, new->type);
		if (new->type == DOUBLE_R || new->type == DOUBLE_L ||
			(new->type >= LESS_AND && new->type <= D_SAND))
			i++;
		if (ft_token_type(s, i) == WORDS)
			i = ft_next_token(s, i, WORDS);
		else if (ft_token_type(s, i) == NUMBERS)
			i = ft_next_token(s, i, NUMBERS);
		else
			i++;
		head = ft_push_token(head, new);
	}
	return (head);
}
