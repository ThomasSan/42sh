#include "lexer.h"
#include "parser.h"

void	ft_display_tokens(t_tree *head, t_env *env, int i, int *fd)
{
	pid_t	pid;

	head->fd[0] = fd[0];
	head->fd[1] = fd[1];
	if (!head)
		return ;
	if (head->types == TUBES)
	{
		pipe(head->fd);
		pid = fork();
		if (pid == 0)
			ft_display_tokens(head->left, env, i, head->fd);
		// else if (pid < 0)
		// 	exit(0); //in case of error
		else
		{
			wait(NULL);
			ft_display_tokens(head->right, env, i, head->fd);			
		}
	}
	else if (head->types != TUBES)
	{
		if (i % 2 == 0)
			ft_start_cmd(head->cmd, env, head->fd);
		else
			ft_start_cmd2(head->cmd, env, head->fd);
		i++;
	}
	if (head->left)
		ft_display_tokens(head->left, env, i, head->fd);
	if (head->right)
		ft_display_tokens(head->right, env, i, head->fd);
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

t_env	*ft_get_env(t_env **env, char *var)
{
	t_env	*new;
	t_env	*tmp;
	int		i;
	int		flag;

	i = 0;
	if (!(new = (t_env *)malloc(sizeof(t_env))))
		return (NULL);
	while (var[i] != '=' && var[i])
		i++;
	flag = var[i] == '=' ? 1 : 0;
	new->name = ft_strsub(var, 0, i);
	new->val = ft_strsub(var, (i + 1), (ft_strlen(var) - i));
	new->next = NULL;
	if (*env == NULL)
		*env = new;
	else
	{
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (*env);
}

void	display_env(t_env *env)
{
	while (env)
	{
		printf("name = %s, val = %s\n", env->name, env->val);
		env = env->next;
	}
}

int		main(int ac, char **av, char **envp)
{
	t_token	*tok;
	t_token	*tmp1;
	t_env	*env;
	t_tree	*head;
	char	*line;
	int		fd[2];

	(void)ac;
	fd[0] = 0;
	fd[1] = 1;
	(void)av;
	while (*envp)
	{
		env = ft_get_env(&env, *envp);
		envp++;
	}
	ft_array_fun();
	while (1)
	{
		head = NULL;
		tok = NULL;
		line = NULL;
		ft_putstr("$> ");
		while(get_next_line(0, &line) == -1);
		if (ft_strncmp(line, "exit", 4) == 0)
			exit(0);
		if (ft_strcmp(line, "") != 0)
		{
			tok = ft_tokeniser(line, tok);
			tok = ft_checking_syntax(tok);
			 tmp1 = tok;
			 while (tmp1)
			 {
			 	printf("type : %d, content : %s\n", tmp1->type, tmp1->content);
			 	tmp1 = tmp1->next;
			 }
			 tree_build_cmd(tok);
			//head = tree_generator(head, tok);
			//ft_display_tokens(head, env, 0, fd);
			//tok = free_token_list(tok);
			//head = delete_tree(head);
		}
		free(line);
	}
	return (0);
			head = tree_generator(head, tok);
			ft_display_tokens(head, env, 0, fd);
			tok = free_token_list(tok);
			head = delete_tree(head);
}
