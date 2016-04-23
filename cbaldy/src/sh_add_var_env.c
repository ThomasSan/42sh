/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_add_var_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 19:10:51 by cbaldy            #+#    #+#             */
/*   Updated: 2016/04/23 14:03:01 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	**sh_copy_env(int size)
{
	int		j;
	char	**tmp;

	if ((tmp = (char **)malloc(sizeof(char *) * (size + 2))) == NULL)
		return (NULL);
	j = 0;
	while (j < size)
	{
		tmp[j] = ft_strdup(g_env[j]);
		j++;
	}
	tmp[size + 1] = NULL;
	return (tmp);
}

int			sh_add_var_env(char *name, char *value)
{
	int		i;
	char	**new_env;

	i = 0;
	while (g_env[i] != NULL)
		i++;
	if ((new_env = sh_copy_env(i)) == NULL)
		return (-1);
	new_env[i] = mod_strjoin(ft_strjoin(name, "="), value, 1);
	ft_free_tab(g_env);
	g_env = new_env;
	return (0);
}

int			sh_rm_var_env(char *name)
{
	int		i[3];
	char	**new_env;

	i[0] = 0;
	while (g_env[i[0]] != NULL)
		i[0]++;
	i[1] = 0;
	i[2] = 0;
	if ((new_env = (char **)malloc(sizeof(char *) * i[0])) == NULL)
		return (0);
	while (i[1] + i[2] < i[0])
	{
		if (ft_strncmp(name, g_env[i[1] + i[2]], ft_strlen(name)) == 0 &&
					g_env[i[1] + i[2]][ft_strlen(name)] == '=')
			i[2]++;
		else
		{
			new_env[i[1]] = ft_strdup(g_env[i[1] + i[2]]);
			i[1]++;
		}
	}
	new_env[i[1]] = NULL;
	ft_free_tab(g_env);
	g_env = new_env;
	return (0);
}

int			sh_change_var_env(char *name, char *value)
{
	int		i;

	if ((i = sh_is_new_var(name)) == -1)
		return (-1);
	free(g_env[i]);
	g_env[i] = mod_strjoin(ft_strjoin(name, "="), value, 1);
	return (0);
}

int			sh_is_new_var(char *com)
{
	int		i;

	i = 0;
	while (g_env[i] != NULL)
	{
		if (ft_strncmp(com, g_env[i], ft_strlen(com)) == 0 &&
				g_env[i][ft_strlen(com)] == '=')
			return (i);
		else
			i++;
	}
	return (-1);
}
