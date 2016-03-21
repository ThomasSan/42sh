#include "lexer.h"
/*
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
*/

int		ft_list_len(t_env *env)
{
	int i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}

char	**get_path_env(t_env *env)
{
	char	*dst;
	char	**array;

	array = NULL;
	dst = NULL;
	while (env)
	{
		if (ft_strcmp("PATH", env->name) == 0)
			dst = ft_strdup(env->val);
		env = env->next;
	}
	if (dst)
	{
		array = ft_strsplit(dst, ':');
		free(dst);
	}
	return (array);
}

char	**lst_to_arr(t_env *env)
{
	char	**dst;
	int		i;

	i = 0;
	if (!(dst = (char **)malloc(sizeof(char *) * ft_list_len(env) + 1)))
		return (NULL);
	while (env)
	{
		dst[i] = ft_catplus(env->name, env->val, '=');
		env = env->next;
		i++;
	}
	dst[i] = NULL;
	return (dst);
}

int		ft_pipe_exec(char **array, t_env *env)
{
	pid_t	pid;
	int		fd[2];

	pipe(fd);
	pid = fork();
	(void)env;
	if (pid == 0)
	{
		dup2(fd[0], 0);
		close(fd[1]);	/* the child does not need this end of the pipe */
		execve(array[0], array, NULL);
		perror(array[0]);
	}
	else if (pid > 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);	/* the parent does not need this end of the pipe */
		execve(array[0], array, NULL);
		perror(array[0]);
	}
	else
	{
		perror("fork");
		exit(1);
	}
	return (1);
}

void	ft_start_cmd(char **cmd, t_env *env, int fd[2])
{
	char	**envp;
	char	**tpath;
	char	*path;
	char	**tmp;

	printf("cmd == %s, fd[0] %d fd[1] %d\n", cmd[0], fd[0], fd[1]);
	dup2(fd[1], 1);
	close(fd[0]);
	tpath = get_path_env(env);
	envp = lst_to_arr(env);
	if ((tmp = tpath) != NULL)
	{
		while (*tpath &&
		execve(path = (ft_catplus(*tpath, cmd[0], '/')), cmd, envp) == -1 && tpath++)
			free(path);
		printf("je suis la\n");
	}
	if (execve(cmd[0], cmd, envp) == -1)
		ft_putendl("command not found");
	free_array(envp);
	free_array(tmp);
	free_array(cmd);
}

void	ft_start_cmd2(char **cmd, t_env *env, int fd[2])
{
	char	**envp;
	char	**tpath;
	char	*path;
	char	**tmp;


	printf("cmd == %s, fd[0] %d fd[1] %d\n", cmd[0], fd[0], fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
	tpath = get_path_env(env);
	envp = lst_to_arr(env);
	if ((tmp = tpath) != NULL)
		while (*tpath &&
		execve(path = (ft_catplus(*tpath, cmd[0], '/')), cmd, envp) == -1 && tpath++)
			free(path);
	if (execve(cmd[0], cmd, envp) == -1)
		ft_putendl("command not found");
	free_array(envp);
	free_array(tmp);
	free_array(cmd);
}
