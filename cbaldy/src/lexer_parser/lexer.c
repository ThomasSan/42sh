/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 11:05:40 by tsanzey           #+#    #+#             */
/*   Updated: 2016/03/03 11:05:42 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		is_word_or(char *s, int i)
{
	if (!ft_isdigit(s[i]))
		return (0);
	if (s[i + 1] != '\0' && s[i + 1] == '>')
			return (1);
	if (s[i - 1] && s[i - 1] == '&')
			return (1);
	return (0);
}

int		ft_other_redirs(char *s, int i, int type)
{
	static const char	*token_types[] = {"\"", "\'", "`", ">", ">>", "<",
	"<<", "|", ";", "&", "~", /*"/", */"\\", "$", "#", "-", "\0"};

	if (s[i + 1] && type == DIPLE_R && s[i + 1] == s[i])
		return (4);
	if (s[i + 1] && type == DIPLE_L && s[i + 1] == s[i])
		return (6);
	if (s[i + 1] && type == DIPLE_R && s[i + 1] == *token_types[AMPERSAND])
		return (GREAT_AND);
	if (s[i + 1] && type == DIPLE_L && s[i + 1] == *token_types[AMPERSAND])
		return (LESS_AND);
	// if (s[i + 1] && type == DIPLE_L && s[i + 1] == *token_types[DIPLE_R])
	// 	return (LESS_GREAT);
	return (type);
}
int		ft_token_type(char *s, int i)
{
	int					type;
	int					j;
	static const char	*token_types[] = {"\"", "\'", "`", ">", ">>", "<",
	"<<", "|", ";", "&", "~",/* "/", */"\\", "$", "#", "-", "\0"};

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
			if (j == 3 || j == 5)
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
	"<<", "|", ";", "&", "~",/* "/", */"\\", "$", "#", "-", "<&", ">&", "<>","\0"};

	if (type == DOUBLE_R || type == DOUBLE_L || type == LESS_AND || type == GREAT_AND)
	{
		if (!(dst = (char *)malloc(sizeof(char) * 3)))
			return (NULL);
		dst = ft_strdup(token_types[type]);
		return (dst);
	}
	i = 0;
	while (s[start + i] && ft_token_type(s, start + i) == -1)
		i++;
	i = i == 0 ? 1 : i;
	if (!(dst = (char *)malloc(sizeof(char) * i + 1)))
		return (NULL);
	ft_bzero(dst, i);
	dst[i] = '\0';
	while (i--)
		dst[i] = s[start + i];
	return (dst);
}

int		ft_next_token(char *s, int start)
{
	int i;

	i = 0;
	while (s[start + i] && ft_token_type(s, start + i) == -1)
		i++;
	return (start + i);
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
		if (new->type == DOUBLE_R || new->type == DOUBLE_L || new->type == LESS_AND ||
			new->type == GREAT_AND)
			i++;
		if (ft_token_type(s, i) == -1)
			i = ft_next_token(s, i);
		else
			i++;
		head = ft_push_token(head, new);
	}
	return (head);
}
