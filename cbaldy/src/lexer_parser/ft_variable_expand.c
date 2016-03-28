#include "lexer.h"
#include "shell.h"

t_token		*ft_variable_expand(t_token *tok)
{
	int		i;
	char	*str;

	if ((i = sh_is_new_var(tok->next->content)) >= 0)
	{
		str = tok->content;
		tok->content = ft_strdup(&(ft_strchr(g_env[i], '=')[1]));
		pop_middle_token(tok->next);
		free(str);
	}
	tok->type = WORDS;
	return (tok);
}

t_token		*check_dollar(t_token *tok)
{
	t_token *tmp;

	tmp = tok;
	while (tmp->next)
	{
		if (tmp->type == DOLLAR)
			tmp = ft_variable_expand(tmp);
		else
			tmp = tmp->next;
	}
	return (tok);
}