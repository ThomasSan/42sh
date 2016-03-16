/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 09:15:28 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/14 18:07:02 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "shell.h"

static int			execute_buildin(char **tabl)
{
	int			ret;

	ret = -2;
	if (ft_strcmp(tabl[0], "cd") == 0)
		ret = change_dir(tabl);
	else if (ft_strcmp(tabl[0], "env") == 0)
		ret = fct_env(tabl);
	else if (ft_strcmp(tabl[0], "setenv") == 0 && tabl[1] == NULL)
		ret = print_env(g_env);
	else if (ft_strcmp(tabl[0], "setenv") == 0)
		ret = chg_env_tab(tabl, 0);
	else if (ft_strcmp(tabl[0], "unsetenv") == 0)
		ret = chg_env_tab(tabl, 1);
	else if (ft_strcmp(tabl[0], "exit") == 0)
		ret = sortie(tabl);
	return (ret);
}

static int			get_command(char *str)
{
	char	*path;
	int		buildin;
	int		ret;
	char	**tabl;

	tabl = ft_strsplit_whitespace(str);
	ret = 0;
	path = NULL;
	g_err = ft_strdup("minishell: command not found:");
	if (tabl[0] == NULL)
		;
	else if ((buildin = execute_buildin(tabl)) != -2)
		ret = buildin;
	else if ((path = find_path(tabl)) != NULL)
		ret = execute_command(tabl, path);
	else if (tabl[0] != NULL && ft_strcmp(tabl[0], "") != 0)
		ft_dprintf(STDERR_FILENO, "%s %s\n", g_err, str);
	if (path != NULL)
		free(path);
	g_print_ch = NULL;
	ft_freetab(tabl);
	free(g_err);
	return (ret);
}

static int			analyse_error(int ret, char *str)
{
	if (ret == 11)
		ft_dprintf(STDERR_FILENO, "minishell: segmentation fault %s\n", str);
	if (ret == 2)
		ft_dprintf(STDOUT_FILENO, "\n");
	return (ret);
}

int					get_prompt(void)
{
	char	*str;
	int		ret;
	char	**tabl;
	int		i;

	str = NULL;
	ret = 0;
	ft_putstr(g_prompt);
	signal(SIGINT, SIG_IGN);
	get_line_of_command(0, &str);
	ft_dprintf(get_fd(0), "\n");
	tabl = ft_strsplit(str, ';');
	i = 0;
	while (tabl[i])
	{
		ret = get_command(tabl[i]);
		analyse_error(ret, tabl[i]);
		i++;
	}
	ft_freetab(tabl);
	free(str);
	return (ret);
}
