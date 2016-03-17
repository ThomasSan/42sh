#include "lexer.h"

int		ft_start_proc(char **array, t_env *env)
{
	pid_t		pid;
	char		**array_env;
	char		**tpath;
	char		**tmp;
	char		*path;

	pid = fork();
	if (pid == 0)
	{
		tpath = get_path_env(env);
		array_env = lst_to_arr(env);
		if ((tmp = tpath) != NULL)
			while (*tpath &&
	execve(path = (ft_catplus(*tpath, array[0], '/')), array, array_env) == -1 && tpath++)
				free(path);
		if (execve(array[0], array, array_env) == -1)
			ft_putendl("command not found");
		free_array(array_env);
		free_array(tmp);
		free_array(array);
		exit(0);
	}
	else
		wait(&pid);
	return (1);
}

int		ft_pipe_exec(char **array, t_env *env)
{
	pid_t	pid;
	int		fd[2];

	pipe(fd);
	pid = fork()
	if (pid == 0)
	{
		dup2(pfd[0], 0);
		close(pfd[1]);	/* the child does not need this end of the pipe */
		execvp(cmd2[0], cmd2);
		perror(cmd2[0]);
	}
	else if (pid > 0)
	{
		dup2(pfd[1], 1);
		close(pfd[0]);	/* the parent does not need this end of the pipe */
		execvp(cmd1[0], cmd1);
		perror(cmd1[0]);
	}
	else
	{
		perror("fork");
		exit(1);
	}
	return (1);
}
