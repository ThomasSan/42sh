/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_ch.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 14:01:22 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/15 11:45:11 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				size_list(t_env *debut)
{
	int			i;
	t_env		*buf;

	i = 0;
	buf = debut;
	while (buf)
	{
		buf = buf->next;
		i++;
	}
	return (i);
}

int				chg_env_tab(char **tabl, int a)
{
	int			i;

	i = 1;
	while (tabl[i])
	{
		if (a == 0)
			add_env(tabl[i]);
		else
			unset_env(tabl[i]);
		i++;
	}
	return (0);
}

char			*get_env_var(char *name)
{
	int		size;
	t_env	*buf;

	buf = g_env;
	size = ft_strlen(name);
	while (buf != NULL && verif_env_value(buf->var, name) != 0)
		buf = buf->next;
	if (buf == NULL)
		return (NULL);
	return (ft_strsub(buf->var, size + 1, ft_strlen(buf->var) - size));
}

char			**retrieve_env(t_env *debut)
{
	t_env	*buf;
	char	**tab;
	int		i;

	buf = debut;
	if ((tab = (char **)malloc(sizeof(char*) * (size_list(debut) + 1))) == NULL)
		return (NULL);
	buf = debut;
	i = 0;
	while (buf != NULL)
	{
		if (ft_strcmp(buf->var, "") != 0)
		{
			tab[i] = ft_strdup(buf->var);
			i++;
		}
		buf = buf->next;
	}
	tab[i] = NULL;
	return (tab);
}
