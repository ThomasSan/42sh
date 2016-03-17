#include "lexer.h"

int		check_next_token(t_token *tok)
{
	if (tok->next)
		return (tok->next->type);
	else
		return (-2);
}

int		check_prev_token(t_token *tok)
{
	if (tok->prev)
		return (tok->prev->type);
	else
		return (-2);
}

t_token		*pop_middle_token(t_token *tok)
{
	if (tok->prev)
	{
		tok->prev->next = tok->next;
		tok->next->prev = tok->prev;
	}
	free(tok->content);
	free(tok);
	return (tok->next);
}

void		return_type_quoted(t_token *tok)
{
	int	is_quoted;

	is_quoted = 0;
	while (tok)
	{
		if (tok->type == QUOTES)
			is_quoted = is_quoted == 1 ? 0: 1;
		if (is_quoted && tok->type != QUOTES)
			tok->type = WORDS;
		if (tok->type == BACKSLASH)
		{
			if (check_next_token(tok) != -1)
			{
				pop_middle_token(tok);
				tok->next->type = WORDS;
			}
		}
		tok = tok->next;
	}
}

void		parse_Error(char *s)
{
	//free all the stuff;
	ft_putstr("Parse error near ");
	ft_putendl(s);
}
/*
void		return_type_redirected(t_token *tok)
{
	while (tok)
	{
		if (tok->type == DIPLE_R)
			rules_for_greater(tok);
		tok = tok->next;
	}
}*/

t_token		*ft_remove_space(t_token *tok)
{
	t_token	*tmp;
	t_token	*head;

	head = tok;
	while (tok)
	{
		tmp = tok;
		tok = tok->next;
		if (tmp->type == WHITESPACE)
		{
			if (head == tmp)
			{
				head = head->next;
				head->prev = NULL;
			}
			else
			{
				tmp->prev->next = tmp->next;
				tmp->next->prev = tmp->prev;
			}
			free(tmp->content);
			free(tmp);
		}
	}
	return (head);
}

t_token		*check_minus(t_token *tok)
{
	t_token	*tmp;

	tmp = tok;
	while (tmp->next)
	{
		if (tmp->type == MINUS && check_next_token(tmp) == WORDS)
		{
			tmp->next->content = ft_strjoin(tmp->content, tmp->next->content);
			tmp->type = WORDS;
			if (tmp == tok)
				tok = tok->next;
			tmp = pop_middle_token(tmp);
		}
		else
			tmp = tmp->next;
	}
	return (tok);
}

t_token		*ft_checking_syntax(t_token *tok)
{
	return_type_quoted(tok);
	tok = check_minus(tok);
	tok = ft_remove_space(tok);
	// tok = ft_quote_removal(tok);
	// return_type_redirected(tok);
	return (tok);
}