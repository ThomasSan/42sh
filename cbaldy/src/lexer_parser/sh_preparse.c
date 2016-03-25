#include "lexer.h"

t_parse	*ft_push_in_tab(t_parse *new, t_token *tok)
{
	int		rows;
	int		i;

	i = 0;
	rows = number_of_rows(tok);
	if (!(new->arg = (char **)malloc(sizeof(char *) * rows + 1)))
		return (NULL);
	while (i < rows)
	{
		new->arg[i] = ft_strdup(tok->content);
		tok = tok->next;
		i++;
	}
	new->arg[i] = NULL;
	new->type = CMD;
	return (new);
}

t_parse	*ft_push_pipe(t_parse *head, t_token *tok)
{
	t_parse	*new;
	t_parse	*tmp;

	if (!(new = (t_parse*)malloc(sizeof(t_parse))))
		return (NULL);
	new->arg = NULL;
	if (tok->type == PIPE || tok->type == SEMICOL)
		new->type = tok->type == PIPE ? TUBES : END;
	if (tok->type == D_PIPE || tok->type == D_SAND)
		new->type = tok->type == D_PIPE ? OR_IF : AND_IF;
	new->next = NULL;
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (head);
}

int			*ft_parse_redir(t_parse **head, t_token *tok)
{
	int		i;
	char	**arg;

	i = 0;
	if ((arg = (char **)malloc(sizeof(char *) * 2)) == NULL)
		return (-1);
	if (tok->type == NUMBER)
	{
		tok = tok->next;
		i++;
	}
	if (tok->type == DIPLE_R || tok->type == DOUBLE_R)
	{
		arg[0] = ft_strdup((i > 0 ? tok->prev->content : "1"));
		arg[1] = ft_strdup(tok->next->content);
	}
	else if (tok->type == DIPLE_L || tok->type == DOUBLE_L)
	{
		arg[1] = ft_strdup((i > 0 ? tok->prev->content : "0"));
		arg[0] = ft_strdup(tok->next->content);
	}
	i += 2;
	return (parse_list_pushback(parse_list_new(arg, tok->type - 2), head) + i);
}
/*
	if (!(new = (t_parse*)malloc(sizeof(t_parse))))
		return (NULL);
	new->arg = NULL;
	new->type = TUBES;
	new->next = NULL;
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (head);
}*/

int			*ft_parse_cmd(t_parse *head, t_token *tok)
{
	t_parse	*new;
	t_parse	*tmp;

	if (!(new = (t_parse*)malloc(sizeof(t_parse))))
		return (NULL);
	new = ft_push_in_tab(new, tok);
	new->next = NULL;
	new->type = CMD;
	if (!head)
		head = new;
	else
	{
		tmp = head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (head);
}

int			*ft_analyse_token(t_parse **head, t_token *tok)
{
	if (tok->type == WORDS)
		return (ft_parse_cmd(head, tok));
	else if (tok->type == PIPE || tok->type == SEMICOL ||
		tok->type == D_PIPE || tok->type == D_SAND)
		head = ft_push_pipe(head, tok);
	else if (tok->type == DIPLE_L || tok->type == DOUBLE_L)
		head = ft_push_input(head, tok);
	else if (tok->type == DIPLE_R || tok->type == DOUBLE_R)
		head = ft_push_output(head, tok);
	return (head);
}

int			print_tok(t_token *tok)
{
	t_token	*tmp;

	tmp = tok;
	while (tmp != NULL)
	{
		printf("%d -> ", tmp->type);
		tmp = tmp->next;
	}
	printf("\n");
	return (0);
}

t_parse		*sh_preparse(t_token *tok)
{
	t_parse *head;
	t_token	*tmp;
	int		i;

	head = NULL;
	//print_tok(tok);
	while (tok)
	{
		if ((i = ft_analyse_token(&head, tok)) < 0)
			return (NULL);
		while (i > 0)
		{
			tmp = tok;
			tok = tok->next;
			if (tmp->content != NULL)
				free(tmp->content);
			free(tmp);
			i--;
		}
	}
	return (head);
}
