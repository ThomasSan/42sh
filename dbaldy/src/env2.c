/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 15:49:14 by dbaldy            #+#    #+#             */
/*   Updated: 2016/02/26 13:59:54 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		suppr_elem(int pos)
{
	t_env		*buf;
	t_env		*del;

	buf = g_env;
	if (pos != 0)
	{
		while (buf->nb != pos - 1)
			buf = buf->next;
		del = buf->next;
		buf->next = del->next;
	}
	else
	{
		del = buf;
		g_env = buf->next;
	}
	buf = buf->next;
	free(del->var);
	del->next = NULL;
	free(del);
	reduce_next(buf);
}

int				verif_env_value(char *var, char *str)
{
	char		**tabl;
	int			ret;

	if ((tabl = (char**)malloc(sizeof(char*) * 2)) == NULL)
		return (-1);
	tabl[1] = ft_strchr(var, '=');
	tabl[0] = ft_strsub(var, 0, ft_strlen(var) - ft_strlen(tabl[1]));
	ret = (ft_strcmp(str, tabl[0]) == 0) ? 0 : 1;
	free(tabl[0]);
	free(tabl);
	return (ret);
}

void			unset_env(char *str)
{
	t_env		*buf;

	buf = g_env;
	if (ft_strchr(str, '=') != NULL)
	{
		ft_dprintf(STDERR_FILENO, "unsetenv %s: Invalid argument\n", str);
		return ;
	}
	while (buf != NULL && verif_env_value(buf->var, str) != 0)
		buf = buf->next;
	if (buf == NULL)
		return ;
	suppr_elem(buf->nb);
	if (ft_strncmp(str, "PS1", 3) == 0)
	{
		free(g_prompt);
		g_prompt = ft_strdup("$> ");
	}
}

void			shell_level(t_env *debut)
{
	t_env	*buf;
	int		level;
	char	*str;
	char	*ptr;

	buf = debut;
	while (buf && ft_strncmp(buf->var, "SHLVL", 5) != 0)
		buf = buf->next;
	if (buf == NULL)
	{
		add_env("SHLVL=1");
		return ;
	}
	level = ft_atoi(ft_strchr(buf->var, '=') + 1) + 1;
	str = ft_strtrunc(buf->var, '=');
	ptr = ft_itoa(level);
	free(buf->var);
	buf->var = ft_strjoin_multiple(3, str, "=", ptr);
	free(str);
	free(ptr);
}

void			change_prompt(char *str)
{
	free(g_prompt);
	g_prompt = ft_strdup(str);
}
