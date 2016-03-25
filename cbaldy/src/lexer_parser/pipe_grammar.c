#include "lexer.h"

int					rules_for_pipes(t_token *tok)
{
	if (check_next_token(tok) == WORDS &&
		(check_prev_token(tok) == WORDS || check_prev_token(tok) == FILENAME))
		return (1);
	return (0);
}