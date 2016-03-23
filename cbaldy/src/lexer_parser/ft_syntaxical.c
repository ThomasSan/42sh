#include "lexer.h"

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

t_tree	*ft_push_to_tab(t_tree *head, t_token *tok)
{
	int		rows;
	int		i;

	i = 0;
	rows = number_of_rows(tok);
	if (!(head->cmd = (char **)malloc(sizeof(char *) * rows + 1)))
		return (NULL);
	while (i < rows)
	{
		head->cmd[i] = ft_strdup(tok->content);
		tok = tok->next;
		i++;
	}
	head->cmd[i] = NULL;
	head->types = CMD;
	return (head);
}

t_tree	*ft_push_pipe(t_tree *head)
{
	t_tree	*new;

	if (!(new = (t_tree*)malloc(sizeof(t_tree))))
		return (NULL);
	if (!(new->cmd = (char **)malloc(sizeof(char *) * 2)))
		return (NULL);
	new->cmd[0] = ft_strdup("|");
	new->cmd[1] = NULL;
	//changer new->cmd par NULL;
	new->types = TUBES;
	new->left = head;
	new->right = NULL;
	head = new;
	return (head);
}

t_tree	*ft_push_cmd(t_tree *head, t_token *tok)
{
	t_tree	*new;

	if (!(new = (t_tree*)malloc(sizeof(t_tree))))
		return (NULL);
	new = ft_push_to_tab(new, tok);
	new->left = NULL;
	new->right = NULL;
	if (!head)
	{
		head = new;
		return (head);
	}
	else if (head->types == TUBES)
		head->right = new;
	else if (head->types == LESS)
		head->left = new;
	else if (head->types == GREAT)
		head->right = new;
	return (head);
}

t_tree	*ft_analyse_token(t_tree *head, t_token *tok)
{
	if (tok->type == PIPE)
		head = ft_push_pipe(head);
	if (tok->type == DIPLE_L)
		head = ft_push_input(head);
	if (tok->type == DIPLE_R || tok->type == DOUBLE_R)
		head = ft_push_output(head);
	return (head);
}
