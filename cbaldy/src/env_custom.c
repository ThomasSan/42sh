/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_custom.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/13 15:44:23 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/24 17:03:44 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	env_op_u(char **com, int i)
{
	if (com[i][2] != '\0')
	{
		if (sh_is_new_var(&(com[i][2])) != -1)
			sh_rm_var_env(&(com[i][2]));
	}
	else if (com[i + 1] != NULL)
	{
		if (sh_is_new_var(com[i + 1]) != -1)
			sh_rm_var_env(com[i + 1]);
		i++;
	}
	else
	{
		ft_dprintf(STDERR_FILENO, "env: option requires an argument -- u\n");
		return (-1);
	}
	return (i + 1);
}

static int	env_op_i(char **com, int i)
{
	int		j;

	j = 1;
	while (j < i)
	{
		if (ft_strchr(com[j], '=') != NULL)
			return (-1);
		j++;
	}
	ft_free_tab(g_env);
	if ((g_env = (char **)malloc(sizeof(char *))) == NULL)
		return (-1);
	g_env[0] = NULL;
	return (i + 1);
}

static int	env_new_var(char **com, int i)
{
	char	**split;

	split = ft_strsplit(com[i], '=');
	if (sh_change_var_env(split[0], &(ft_strchr(com[i], '=')[1])) < 0)
		sh_add_var_env(split[0], &(ft_strchr(com[i], '=')[1]));
	ft_free_tab(split);
	return (i + 1);
}

int			env_custom(char **com)
{
	int		i;

	i = 1;
	while (com[i] != NULL)
	{
		if (com[i][0] == '-' && com[i][1] == 'u')
		{
			if ((i = env_op_u(com, i)) < 0)
				return (-1);
		}
		else if (com[i][0] == '-' && com[i][1] == 'i')
		{
			if ((i = env_op_i(com, i)) < 0)
				return (-1);
		}
		else if (ft_strchr(com[i], '=') != NULL)
		{
			if ((i = env_new_var(com, i)) < 0)
				return (-1);
		}
		else
			return (i);
	}
	return (i);
}
