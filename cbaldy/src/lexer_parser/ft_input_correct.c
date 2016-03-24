#include "lexer.h"

int		ft_command_isvalid(t_token *tok)
{
	printf("cmd %s, type %d \n", tok->content, tok->type);
	if (tok->type == WORDS || tok->type == NUMBERS)
	{
		if (tok->next)
			return (ft_command_isvalid(tok->next));
		else
			return (1);
	}
	else if (g_f[tok->type](tok))
	{
		if (tok->next)
			return (ft_command_isvalid(tok->next));
		else
			return (1);
	}
	else
	{
		parse_error(tok->content);
		return (0);
	}
}
