#include "lexer.h"

void	ft_array_fun(void)
{
	g_f[DIPLE_R] = rules_for_less;
	g_f[DOUBLE_R] = rules_for_less;
	g_f[DIPLE_L] = rules_for_great;
	g_f[DOUBLE_L] = rules_for_great;
	g_f[PIPE] = rules_for_pipes;
	g_f[MINUS] = rules_for_minus;
	g_f[GREAT_AND] = rules_for_great_and;
	g_f[LESS_AND] = rules_for_less_and;
	g_f[AND_GREAT] = rules_for_and_great;
	g_f[D_PIPE] = rules_for_orandif;
	g_f[D_SAND] = rules_for_orandif;
}

void		parse_error(char *s)
{
	ft_putstr("Parse error near ");
	ft_putendl(s);
}

int		number_of_rows(t_token *tok)
{
	t_token	*tmp;
	int		i;

	tmp = tok;
	i = 0;
	while (tmp && tmp->type == WORDS)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
