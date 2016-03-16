/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ope_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 09:59:40 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/14 18:06:47 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void			create_var(char *str)
{
	t_env	*buf;
	t_env	*new;

	buf = g_env;
	if ((new = (t_env*)malloc(sizeof(t_env))) == NULL)
		exit(1);
	while (buf && buf->next != NULL)
		buf = buf->next;
	new->var = ft_strdup(str);
	new->next = NULL;
	new->nb = (buf == NULL) ? 0 : buf->nb + 1;
	if (buf == NULL)
		g_env = new;
	else
		buf->next = new;
}

static char			**new_var(char *str)
{
	char	**tabl;

	if ((tabl = (char**)malloc(sizeof(char*) * 3)) == NULL)
		return (NULL);
	tabl[1] = ft_strdup(ft_strchr(str, '=') + 1);
	tabl[0] = ft_strsub(str, 0, ft_strlen(str) - ft_strlen(tabl[1]) - 1);
	tabl[2] = NULL;
	return (tabl);
}

void				add_env(char *str)
{
	char		**tabl;
	char		*buf;

	if (ft_strchr(str, '=') == NULL)
	{
		ft_dprintf(STDERR_FILENO,
				"setenv: No such file or directory: %s\n", str);
		return ;
	}
	if ((tabl = new_var(str)) == NULL)
		return ;
	if (tabl[1] == NULL && ft_freetab(tabl) == 0)
		return ;
	tabl[1] = free_quotes(tabl[1]);
	if (ft_strcmp(tabl[0], "PS1") == 0)
		change_prompt(tabl[1]);
	if ((buf = get_env_var(tabl[0])) != NULL)
	{
		change_env_var(tabl[0], tabl[1]);
		ft_freetab(tabl);
		free(buf);
		return ;
	}
	create_var(str);
	ft_freetab(tabl);
}

int					print_env(t_env *debut)
{
	t_env		*buf;

	buf = debut;
	while (buf != NULL && ft_strcmp(buf->var, "") != 0)
	{
		ft_dprintf(STDOUT_FILENO, "%s\n", buf->var);
		buf = buf->next;
	}
	return (0);
}

char				*substitute(char *first, char *second)
{
	char	*pwd;
	char	*new;
	char	*home;

	pwd = get_env_var("PWD");
	new = ft_replace_str(pwd, first, second);
	if (ft_strcmp(new, pwd) != 0)
	{
		if ((home = get_env_var("HOME")) == NULL)
			home = ft_strdup("");
		g_print_ch = ft_replace_str(new, home, "~");
		free(pwd);
		free(home);
		return (new);
	}
	free(pwd);
	free(new);
	ft_dprintf(STDERR_FILENO, "cd: %s: not in pwd\n", second);
	return (NULL);
}
