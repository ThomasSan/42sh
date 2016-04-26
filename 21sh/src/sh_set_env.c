/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_set_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 15:48:41 by cbaldy            #+#    #+#             */
/*   Updated: 2016/04/26 19:03:41 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_malloc_env(char **env)
{
	int		i[2];

	i[0] = 0;
	while (env[i[0]] != NULL)
		i[0]++;
	if ((g_env = (char **)malloc(sizeof(char *) * (i[0] + 1))) == NULL)
		exit(-1);
	i[1] = 0;
	while (i[1] < i[0])
	{
		g_env[i[1]] = ft_strdup(env[i[1]]);
		i[1]++;
	}
	g_env[i[1]] = NULL;
}

static void	sh_std_env(void)
{
	char	*path;

	if ((path = getcwd(NULL, 0)) == NULL)
		path = ft_strdup("(null)");
	if (sh_is_new_var("PWD") < 0)
		sh_add_var_env("PWD", path);
	if (sh_is_new_var("OLDPWD") < 0)
		sh_add_var_env("OLDPWD", path);
	free(path);
}

static int	sh_set_local_env(void)
{
	if ((g_local = (t_local *)malloc(sizeof(t_local))) == NULL)
		return (-1);
	g_local->curs = 0;
	g_local->le_mode = 0;
	g_local->exit_value = 0;
	g_paste = NULL;
	return (0);
}

int			sh_set_env(char **env)
{
	int			i;
	char		*nb_shlvl;

	sh_malloc_env(env);
	sh_std_env();
	if ((i = sh_is_new_var("SHLVL")) < 0)
		sh_add_var_env("SHLVL", "1");
	else
	{
		nb_shlvl = ft_itoa(ft_atoi(&(ft_strchr(g_env[i], '=')[1])) + 1);
		sh_change_var_env("SHLVL", nb_shlvl);
		free(nb_shlvl);
	}
	hash_get_tab();
	if (sh_set_local_env() < 0)
		return (-1);
	return (0);
}
