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
#include "parser.h"

int		ft_token_type(char *s, int i)
{
	int					type;
	int					j;
	static const char	*token_types[] = {"\"", "\'", "`", ">", ">>", "<",
	"<<", "|", ";", "&", "~", "/", "\\", "$", "#", "-", "\0"};

	type = -1;
	j = 0;
	while (*token_types[j])
	{
		if (s[i] == *token_types[j])
		{
			type = j;
			if (s[i + 1] && j == 3 && s[i + 1] == s[i])
				return (4);
			if (s[i + 1] && j == 5 && s[i + 1] == s[i])
				return (6);
			return (type);
		}
		j++;
	}
	return (type);
}

char	*tok_content(char *s, int start, int type)
{
	int		i;
	char	*dst;

	if (type == 4 || type == 6)
	{
		if (!(dst = (char *)malloc(sizeof(char) * 3)))
			return (NULL);
		if (type == 4)
			dst = ft_strdup(">>");
		if (type == 6)
			dst = ft_strdup("<<");
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
	if (!head)
		head = new;
	else
	{
		tmp = head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
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
		if (new->type == 4 || new->type == 6)
			i++;
		if (ft_token_type(s, i) == -1)
			i = ft_next_token(s, i);
		else
			i++;
		head = ft_push_token(head, new);
	}
	return (head);
}
