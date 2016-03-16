/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/14 17:26:28 by dbaldy            #+#    #+#             */
/*   Updated: 2016/02/27 14:58:25 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		analyse_opt(char *str)
{
	int		j;
	int		opt;

	j = 1;
	opt = 0;
	while (str[j])
	{
		if (str[j] == 'i' && (opt == 0 || opt == 1))
			opt = (opt == 2) ? -1 : 1;
		else if (str[j] == 'u' && (opt == 0 || opt == 2))
			opt = (opt == 1) ? -1 : 2;
		else
			opt = -(unsigned char)str[j];
		if (opt < 0)
			break ;
		j++;
	}
	return (opt);
}

static int		*opt_env(char **tabl)
{
	int		i;
	int		*opt;

	if ((opt = (int*)malloc(sizeof(int) * 2)) == NULL)
		return (NULL);
	opt[0] = 0;
	opt[1] = 1;
	i = 1;
	while (tabl[i] && tabl[i][0] == '-')
	{
		if ((opt[0] = analyse_opt(tabl[i])) < 0)
			break ;
		i++;
	}
	opt[1] = i;
	return (opt);
}

static int		manage_opt(char **tabl, int *opt)
{
	int		i;
	char	*str;

	i = opt[1];
	str = NULL;
	if (opt[0] < 0)
	{
		free(opt);
		ft_dprintf(STDERR_FILENO, "%s%c\n%s%s\n", "env: illegal option -- ",
		(unsigned char)-opt[0], "usage: env [-i] [-u name] [name=value]",
				" [utility [argument ...]]");
		return (-1);
	}
	if (opt[0] == 1)
		free_env(&g_env);
	else if (opt[0] == 2)
		while (tabl[i] &&
				(str = find_path(&tabl[i])) == NULL)
		{
			unset_env(tabl[i]);
			i++;
		}
	if (str != NULL)
		free(str);
	return (0);
}

static int		interpret_str(char **tabl)
{
	int		*opt;
	char	*path;

	opt = opt_env(tabl);
	path = NULL;
	if (manage_opt(tabl, opt) < 0)
		return (-1);
	while (tabl[opt[1]] && opt[0] != 2)
	{
		if ((path = find_path(&tabl[opt[1]])) != NULL)
			break ;
		add_env(tabl[opt[1]]);
		opt[1]++;
	}
	if (path == NULL)
		print_env(g_env);
	else
		execute_command(&tabl[opt[1]], path);
	free(opt);
	return (0);
}

int				fct_env(char **tabl)
{
	pid_t	pere;
	int		ret;

	pere = fork();
	if (pere == 0)
	{
		interpret_str(tabl);
		if (g_env != NULL)
			free_env(&g_env);
		return (-1);
	}
	if (pere > 0)
	{
		wait(&ret);
		if (ret == 11)
			ft_dprintf(STDERR_FILENO, "env: segmentation fault %s\n", tabl[0]);
	}
	return (0);
}
