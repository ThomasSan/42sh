#include "lexer.h"
#include "parser.h"

void	ft_display_tokens(t_tree *head)
{
	printf("head %s\n", head->cmd[0]);
	if (head->left)
		ft_display_tokens(head->left);
	if (head->right)
		ft_display_tokens(head->right);
}

// t_tree	*delete_tree(t_tree *head)
// {
// 	t_tree	*tmp;
// 	t_tree	*node;

// 	tmp = head;
// 	if (tmp != NULL)
// 	{
// 		while (tmp)
// 		{
// 			node = tmp;
// 			tmp = tmp->next;
// 			free(node->content);
// 			free(node);
// 			// printf("free : %s ptr : %p\n", node->content, node);
// 		}
// 	}
// 	head = NULL;
// 	return (head);
// }

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

	while(1)
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
		while (tmp1)
		{
			printf("type : %d, content : %s\n", tmp1->type, tmp1->content);
			tmp1 = tmp1->next;
		}
		head = tree_generator(head, tok);
		ft_display_tokens(head);
		// head = delete_tree(head);
		tok = free_token_list(tok);
		free(line);
	}
	return (0);
}