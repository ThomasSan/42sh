/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_interpret_com.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 15:43:04 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/22 19:42:31 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_exec_list	g_exec_list[] = {
	{0, &exec_cmd},
	{5, &exec_pipe},
	{-1, NULL},
};

static int	sh_interpret(t_tree *root)
{
	int		i;

	i = 0;
	while (g_exec_list[i].id != -1)
	{
		if (g_exec_list[i].id == root->types)
			g_exec_list[i].f(root);
		i++;
	}
	return (0);
}

int			sh_exec_list(char *str)
{
	t_tree		*root;
	int			s[3];

	if ((root = sh_lexer_parser(str)) != NULL)
		ft_putendl("LEXER_PARSER: OK");
	s[0] = dup(STDIN_FILENO);
	s[1] = dup(STDOUT_FILENO);
	s[2] = dup(STDERR_FILENO);
	sh_interpret(root);
	dup2(s[0], STDIN_FILENO);
	dup2(s[1], STDOUT_FILENO);
	dup2(s[2], STDERR_FILENO);
	close(s[0]);
	close(s[1]);
	close(s[2]);
	return (0);
}

int		exec_cmd(t_tree *root)
{
	sh_execute(root->cmd);
	return (0);
}

int		exec_pipe(t_tree *root)
{
	int		fd[2];

	pipe(fd);
	close(fd[0]);
	close(fd[1]);
	sh_interpret(root->left);
	return (0);
	root = NULL;
}
/*
static int	sh_pipe(t_exec_list *tmp)
{
	int			fd[2];
	pid_t		pid;
	int			i;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		sh_execute(tmp->arg);
		close(fd[1]);
		exit(0);
	}
	else if (pid > 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		wait(&i);
	}
	return (0);
}

static int	sh_output(t_exec_list *tmp)
{
	mode_t	mode;
	int		opt;
	int		fd_1;
	int		fd_2;
	int fd[2];

	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	opt = O_RDWR | O_CREAT | O_TRUNC;
	if (tmp->clog == 5)
		opt |= O_APPEND;
	tmp = tmp->next;
	fd_1 = open(tmp->arg[0], opt, mode);
	fd_2 = dup(STDOUT_FILENO);
	ft_printf("%d ", fd_2);

	pid_t	pid;
	int		i;
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd_1, STDOUT_FILENO);
		tmp = tmp->previous;
		sh_execute(tmp->arg);
		exit(0);
	}
	else if (pid > 0)
	{
		dup2(fd[0], STDIN_FILENO);
		wait(&i);
	}
	close(fd_1);
	return (0);
}*/
