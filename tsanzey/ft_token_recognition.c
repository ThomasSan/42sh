#include "lexer.h"

void		return_type_quoted(t_token *tok)
{
	int	is_quoted;
	int	slashed;

	is_quoted = 0;
	slashed = 0;
	while (tok)
	{
		if (tok->type == 0)
			is_quoted = is_quoted == 1 ? 0: 1;
		if (is_quoted && tok->type != 0)
			tok->type = -1;
		tok = tok->next;
	}
}

t_token		*ft_checking_syntax(t_token *tok)
{
	return_type_quoted(tok);
	return (tok);
}