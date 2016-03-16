/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 13:33:02 by dbaldy            #+#    #+#             */
/*   Updated: 2016/02/26 19:43:00 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		empty_env(void)
{
	char	*pwd;
	char	*buf;
	char	*str;

	pwd = NULL;
	pwd = getcwd(pwd, 1000);
	if ((str = get_env_var("SHLVL")) == NULL)
		add_env("SHLVL=0");
	if (str != NULL)
		free(str);
	buf = ft_strjoin("PWD=", pwd);
	if ((str = get_env_var("PWD")) == NULL)
		add_env(buf);
	free(buf);
	if (str != NULL)
		free(str);
	free(pwd);
}

static void		check_env(char *name)
{
	char	*pwd;
	char	*buf;
	char	*str;

	pwd = NULL;
	pwd = getcwd(pwd, 1000);
	buf = ft_strjoin("OLDPWD=", pwd);
	if ((str = get_env_var("OLDPWD")) == NULL)
		add_env(buf);
	free(buf);
	free(str);
	buf = ft_strjoin_multiple(4, "_=", pwd, "/", name);
	if ((str = get_env_var("_")) == NULL)
		add_env(buf);
	free(buf);
	free(str);
	free(pwd);
}

t_env			*get_env(char **env, char *name)
{
	int		i;

	i = 0;
	while (env[i] != NULL)
	{
		add_env(env[i]);
		i++;
	}
	check_env(name);
	empty_env();
	return (g_env);
}

void			change_env_var(char *name, char *new)
{
	char		*new_env;
	t_env		*buf;

	buf = g_env;
	while (buf && buf->next != NULL && verif_env_value(buf->var, name) != 0)
		buf = buf->next;
	if (buf && buf->next == NULL && verif_env_value(buf->var, name) != 0)
	{
		new_env = ft_strjoin_multiple(3, name, "=", new);
		add_env(new_env);
		free(new_env);
	}
	else
	{
		free(buf->var);
		buf->var = ft_strjoin_multiple(3, name, "=", new);
	}
}
