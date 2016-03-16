/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/13 16:20:19 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/14 16:36:51 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "shell.h"

char			*direct_path(char *str)
{
	char	*ret;
	char	**tabl;

	tabl = ft_strsplit_whitespace(str);
	if ((ret = verif_exe(tabl[0], 0)) != NULL)
	{
		ft_freetab(tabl);
		free(str);
		return (ret);
	}
	ft_freetab(tabl);
	return (NULL);
}

void			treat_minus(char *str)
{
	char	*buf;
	char	*home;

	buf = ft_strdup(str);
	buf = clean_pwd(buf);
	if ((home = get_env_var("HOME")) == NULL)
		ft_dprintf(STDERR_FILENO, "HOME not set\n");
	else
	{
		buf = ft_replacestr(buf, home, "~");
		free(home);
	}
	free(buf);
}

void			free_env(t_env **debut)
{
	t_env	*buf;
	t_env	*suiv;

	buf = *debut;
	suiv = buf->next;
	*debut = NULL;
	while (buf)
	{
		free(buf->var);
		free(buf);
		buf = suiv;
		suiv = (suiv == NULL) ? NULL : buf->next;
	}
}

int				sortie(char **tabl)
{
	int		ret;

	if (size_tab(tabl) > 2)
	{
		ft_dprintf(STDERR_FILENO, "exit: too many arguments\n");
		return (0);
	}
	ret = (tabl[1] != NULL) ? ft_atoi(tabl[1]) : 0;
	free_env(&g_env);
	free(g_err);
	reset_term();
	exit(ret);
}

char			*free_quotes(char *str)
{
	char		*buf;

	if (ft_strlen(str) == 3 && str[0] == '"' && str[1] == '~' && str[2] == '"')
		return (str);
	if (str[0] == '"' && str[ft_strlen(str) - 1] == '"')
	{
		buf = ft_strsub(str, 1, ft_strlen(str) - 2);
		free(str);
		return (buf);
	}
	return (str);
}
