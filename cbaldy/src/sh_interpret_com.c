/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_interpret_com.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 15:43:04 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/14 13:08:11 by cbaldy           ###   ########.fr       */
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

/*static int	**sh_prepare_exec(t_exec_list *begin)
{
	int			**fds;
	int			i;
	t_exec_list	*tmp;

	i = exec_list_count(begin);
	if ((fds = (int **)malloc(sizeof(int *) * (i + 1))) == NULL)
		return (NULL);
	i = 0;
	while (begin->next != NULL)
	{
		fds[i] = malloc(sizeof(int) * 2);
		pipe(fds[i]);
		if (begin->clog == 3 || begin->clog == 5)
			fds[i][0] = open(begin->next->arg[0]

	}
}*/

static int	sh_interpret(char *str)
{
	t_exec_list	*begin;
	//t_exec_list	*tmp;
	char		**com;
	int			i;
	//int			**fds;

	if ((begin = parse_build_com(str)) == NULL)
		return (0);
	//fds	= sh_prepare_exec(begin);
	com = begin->arg;
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

int			sh_split_com(char *str)
{
	char	**split;
	int		i;

	split = ft_strsplit(str, ';');
	i = 0;
	while (split[i] != NULL)
	{
		sh_interpret(split[i]);
		i++;
	}
	ft_free_tab(split);
	return (0);
}
