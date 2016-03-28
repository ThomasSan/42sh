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
			is_quoted = is_quoted == 1 ? 0: 1;
		// if (is_quoted && tok->type == DOLLAR)
			// ft_variable_expand(tok);
		if (is_quoted && tok->type != QUOTES)
			tok->type = WORDS;
		if (tok->type == BACKSLASH)
		{//je pense monter cette fonction en premier en cas de \" Et puis verifier si une cmd start avec : '\'
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

int 		ft_edit_useless(t_token *tok)
{
	while (tok)
	{
		if (tok->type == AMPERSAND || tok->type == DOLLAR)
			tok->type = WORDS;
		tok = tok->next;
	}
	return (1);
}

t_parse		*ft_checking_syntax(t_token *tok)
{
	tok = check_dollar(tok);
	// printf("dollar check\n");
	return_type_quoted(tok);
	tok = join_quoted(tok);
	// printf("QUOTES check\n");
	tok = check_minus(tok);
	// printf("MINUS check\n");
	tok = ft_tild_expand(tok);
	// printf("TILD check\n");
	// fonction pour chager les autres tokens en word et pop les inutiles
	ft_edit_useless(tok);
	tok = ft_token_removal(tok, WHITESPACE);
	// printf("SPACES check\n");
	tok = ft_token_removal(tok, QUOTES);
	// printf("QUOTES check\n");
	ft_display_tokens(tok);
	if (!(ft_command_isvalid(tok)))
		return (NULL);
	return (parse_build_list(tok));
}
