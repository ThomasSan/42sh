#include "lexer.h"
#include "parser.h"

void	ft_display_tokens(t_tree *head)
{
	int	i;

	i = 0;
	if (!head)
		return ;
	while (head->cmd[i])
	{
		printf("head %s\n", head->cmd[i]);
			i++;
	}
	if (head->left)
		ft_display_tokens(head->left);
	if (head->right)
		ft_display_tokens(head->right);
}

t_tree	*delete_tree(t_tree *head)
{
	if (!head)
		return (NULL);
	if (head->left)
		delete_tree(head->left);
	if (head->right)
		delete_tree(head->right);
	free_array(head->cmd);
	free(head);
	free(head->cmd);
	return (head);
}

t_token	*free_token_list(t_token *tok)
{
	t_token	*tmp;

	while (tok)
	{
		tmp = tok;
		tok = tok->next;
		free(tmp->content);
		free(tmp);
	}
	return (tok);
}

int		main(void)
{
	t_token	*tok;
	t_token	*tmp1;
	t_tree	*head;
	char	*line;

	while (1)
	{
		head = NULL;
		tok = NULL;
		line = NULL;
		ft_putstr("$> ");
		while(get_next_line(0, &line) == -1);
		if (ft_strncmp(line, "exit", 4) == 0)
			exit(0);
		tok = ft_tokeniser(line, tok);
		tok = ft_checking_syntax(tok);
		tmp1 = tok;
		// while (tmp1)
		// {
		// 	printf("type : %d, content : %s\n", tmp1->type, tmp1->content);
		// 	tmp1 = tmp1->next;
		// }
		head = tree_generator(head, tok);
		printf("ed %p\n", head);
		ft_display_tokens(head);
		printf("displlay ok\n");
		tok = free_token_list(tok);
		head = delete_tree(head);
		printf("delete oks\n");
		free(line);
	}
	return (0);
}