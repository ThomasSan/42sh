#include "lexer.h"

t_tree	*ft_push_output(t_tree *head)
{
	t_tree	*new;

	if (!(new = (t_tree*)malloc(sizeof(t_tree))))
		return (NULL);
	if (!(new->cmd = (char **)malloc(sizeof(char *) * 2)))
		return (NULL);
	new->cmd[0] = ft_strdup("> or >>");
	new->cmd[1] = NULL;
	//changer new->cmd par NULL;
	new->types = O_REDIR;
	new->left = head;
	new->right = NULL;
	head = new;
	return (head);
}

t_tree	*ft_push_input(t_tree *head)
{
	t_tree	*new;

	if (!(new = (t_tree*)malloc(sizeof(t_tree))))
		return (NULL);
	if (!(new->cmd = (char **)malloc(sizeof(char *) * 2)))
		return (NULL);
	new->cmd[0] = ft_strdup("<");
	new->cmd[1] = NULL;
	//changer new->cmd par NULL;
	new->types = I_REDIR;
	new->left = NULL;
	new->right = head;
	head = new;
	return (head);
}