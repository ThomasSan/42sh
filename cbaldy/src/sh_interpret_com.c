/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_interpret_com.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 15:43:04 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/15 19:18:50 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_builtin	g_list_builtin[] = {
	{"cd", &sh_builtin_cd},
	{"env", &sh_builtin_env},
	{"exit", &sh_builtin_exit},
	{"setenv", &sh_builtin_setenv},
	{"unsetenv", &sh_builtin_unsetenv},
};

static int	sh_error_msg(char **com, int error)
{
	int		fd;

	fd = STDERR_FILENO;
	if (error == 2)
		ft_dprintf(STDIN_FILENO, "\n");
	if (error == 11)
		ft_dprintf(fd, "shell: segmentation fault  %s\n", com[0]);
	return (0);
}

static int	sh_execute(char **com)
{
	int		i;

	i = 0;
	while (i < 5 && com[0] != NULL)
	{
		if (ft_strncmp(com[0], g_list_builtin[i].name,
					ft_strlen(g_list_builtin[i].name)) == 0 &&
				com[0][ft_strlen(g_list_builtin[i].name)] == '\0')
			return (g_list_builtin[i].f(com));
		i++;
	}
	if (com[0] != NULL)
		i = sh_command(com);
	if (i != 0)
		sh_error_msg(com, i);
	ft_free_tab(com);
	return (0);
}

static int	sh_pipe(t_exec_list *tmp)
{
	int			fd[2];
	pid_t		pid;
	int	i;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		sh_execute(tmp->arg);
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
	int		fd_o;
	char	buf;

	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	opt = O_WRONLY | O_CREAT;
	if (tmp->clog == 5)
		opt |= O_APPEND;
	tmp = tmp->next;
	fd_o = open(tmp->arg[0], opt, mode);
	while (read(STDIN_FILENO, &buf, 1) > 0)
		write(fd_o, &buf, 1);
	return (0);
}

static int	sh_interpret(t_exec_list *tmp)
{
	if (tmp->clog == 1)
		sh_pipe(tmp);
	else if (tmp->clog == 3 || tmp->clog == 5)
	{
		sh_pipe(tmp);
		sh_output(tmp);
	}
	else if (tmp->previous == NULL || tmp->previous->clog != 0)
		sh_execute(tmp->arg);
	return (0);
}

int			sh_exec_list(char *str)
{
	t_exec_list	*begin;
	t_exec_list	*tmp;

	if ((begin = parse_build_com(str)) == NULL)
		return (0);
	tmp = begin;
	while (tmp != NULL)
	{
		sh_interpret(tmp);
		tmp = tmp->next;
	}
	dup2(1, STDIN_FILENO);
	return (0);
}
