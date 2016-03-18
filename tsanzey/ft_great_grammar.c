#include "lexer.h"


//creer des fonctions pour checker apres l'ampersand

int			rules_for_great(t_token *tok)
{
	if (check_next_token(tok) == AMPERSAND)
	{
		if (tok->next)
			return (ft_command_isvalid(tok->next));
		else
			return (0);
	}
	if (check_next_token(tok) == WORDS)
		return (1);
	return (0);
}