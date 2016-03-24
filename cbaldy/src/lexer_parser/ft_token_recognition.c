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

void		return_type_quoted(t_token *tok)
{
	int	is_quoted;

	is_quoted = 0;
	while (tok)
	{
		if (tok->type == QUOTES)
			is_quoted = is_quoted == 1 ? 0: 1;
		if (is_quoted && tok->type == DOLLAR)
			ft_variable_expand(tok);
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

t_token		*ft_token_removal(t_token *tok, t_sym sym)
{
	t_token *tmp;

	tmp = tok;
	while (tmp)
	{
		if(tmp->type == sym)
		{
			if (tok == tmp)
				tok = tok->next;
			tmp = pop_middle_token(tmp);
		}
		else
			tmp = tmp->next;
	}
	return(tok);
}

void		ft_display_tokens(t_token *tok)
{
	while (tok)
	{
		printf("t : %s, type : %d\n", tok->content, tok->type);
		tok = tok->next;
	}
}

t_token		*ft_checking_syntax(t_token *tok)
{
	return_type_quoted(tok);
	// function pour join les quoted;
	// printf("QUOTES check\n");
	tok = check_minus(tok);
	// printf("MINUS check\n");
	tok = ft_tild_expand(tok);
	// printf("TILD check\n");
	// fonction pour chager les autres tokens en word et pop les inutiles
	tok = ft_token_removal(tok, WHITESPACE);
	// printf("SPACES check\n");
	tok = ft_token_removal(tok, QUOTES);
	// printf("QUOTES check\n");
	// ft_display_tokens(tok);
	if (!ft_command_isvalid(tok))
		return (NULL);
	return (tok);
}
