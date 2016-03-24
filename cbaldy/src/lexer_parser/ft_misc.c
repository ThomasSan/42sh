#include "lexer.h"

void	ft_array_fun(void)
{
	g_f[DIPLE_R] = rules_for_great;
	// g_f[DOUBLE_R] = rules_for_great;
	//g_f[DIPLE_L] = rules_for_less;
	// g_f[DOUBLE_L] = rules_for_less;
	g_f[PIPE] = rules_for_pipes;
	// g_f[TILD] = ;
	// g_f[MINUS] = rules_for_minus;
	// g_f[GREAT_AND] = rules_for_redir;
	// g_f[LESS_AND] = rules_for_redir;
}

void		parse_error(char *s)
{
	ft_putstr("Parse error near ");
	ft_putendl(s);
}
