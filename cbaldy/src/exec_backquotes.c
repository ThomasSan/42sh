/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_backquotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 09:36:53 by cbaldy            #+#    #+#             */
/*   Updated: 2016/04/27 15:38:39 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*bq_format_string(char *str)
{
	int		i;

	if (str[0] == '\0')
	{
		free(str);
		return (NULL);
	}
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			str[i] = ' ';
		i++;
	}
	return (str);
}

char	*exec_backquotes(t_tree *root)
{
	pid_t	pid;
	int		fd[2];
	int		ret;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		ret = sh_interpret(root);
		close(fd[1]);
		exit(ret);
	}
	else if (pid > 0)
	{
		char	*str;
		char	buf[2];
		str = ft_strdup("");
		close(fd[1]);
		buf[1] = '\0';
		while (read(fd[0], &(buf[0]), 1) > 0)
			str = mod_strjoin(str, buf, 1);
		wait(&ret);
		close(fd[0]);
		exec_free_root(root);
		return (bq_format_string(str));
	}
	return (NULL);
}
