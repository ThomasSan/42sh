/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 15:15:03 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/15 11:18:30 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int		ft_control(char ***com, char **path, int index)
{
	pid_t	pid;
	int		i;
	int		fd[2];

	if (com[index + 1] != NULL)
		pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		if (com[index + 1] != NULL)
		{
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
		}
		if (path[index] != NULL)
			execve(path[index], com[index], 0);
		else
		{
			mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
			int		fff = open("1", O_WRONLY | O_CREAT | O_APPEND, mode);
			char	buf;
			while (read(STDIN_FILENO, &buf, 1) > 0)
				write(fff, &buf, 1);
		}
	}
	else if (pid != 0)
	{
		if (com[index + 1] == NULL)
			exit(0);
		else
		{
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			ft_control(com, path, index + 1);
		}
	}
	return (0);
}

int		main(void)
{
	int		i;
	char	***com;
	char	**path;

	com = malloc(sizeof(char **) * 5);
	path = malloc(sizeof(char *) * 4);
	i = 0;
	while (i < 3)
	{
		com[i] = malloc(sizeof(char *) * 3);
		i++;
	}
	com[i] = malloc(sizeof(char *) * 2);
	com[i][0] = strdup("1");
	com[i][1] = NULL;
	path[3] = NULL;
	i++;
	com[i] = NULL;
	path[0] = strdup("/bin/ls");
	path[1] = strdup("/usr/bin/wc");
	path[2] = strdup("/bin/cat");
	com[0][0] = strdup("ls");
	com[0][1] = strdup("-l");
	com[0][2] = NULL;
	com[2][0] = strdup("cat");
	com[2][1] = strdup("-en");
	com[2][2] = NULL;
	com[1][0] = strdup("wc");
	com[1][1] = strdup("-l");
	com[1][2] = NULL;

	ft_control(com, path, 0);
	return (0);
}
/*
	pipe(fd);
	char	buf;
	pid = fork();
	if (pid == 0)
	{
		int		fds[2];
		pipe(fds);
		close(fd[1]);
		//dup2(fd[0], STDIN_FILENO);
		dup2(fds[1], STDOUT_FILENO);
		int		pids = fork();

		if (pids == 0)
		{
			mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
			int		fff = open("1", O_WRONLY | O_CREAT, mode);
			//close(fds[1]);
			//int d = dup(fd[0]);
			//dup2(fds[0], STDIN_FILENO);
			char	buf;
			while (read(fd[0], &buf, 1) > 0)
				write(fff, &buf, 1);
		}
		else if (pids != 0)
		{
			dup2(fd[0], STDIN_FILENO);
			dup2(fds[0], STDIN_FILENO);
			int		lvl[2];
			pipe(lvl);
			int		pids2 = fork();
			if (pids2 == 0)
			{
				dup2(lvl[0], STDIN_FILENO);
				execve("/bin/cat", com[1], 0);
			}
			else if (pids2 != 0)
			{
				dup2(lvl[1], STDOUT_FILENO);
				execve("/usr/bin/wc", com[2], 0);
			}
		}
	}
	else if (pid != 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		execve("/bin/ls", com[0], 0);
	}
	return (0);
}*/
