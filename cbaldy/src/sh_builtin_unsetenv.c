/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_unsetenv.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 11:38:34 by cbaldy            #+#    #+#             */
/*   Updated: 2016/02/12 12:26:06 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	unsetenv_find_var(char *name)
{
	int		i;

	i = 0;
	while (g_env[i] != NULL)
	{
		if (ft_strncmp(name, g_env[i], ft_strlen(name))
				== 0 && g_env[i][ft_strlen(name)] == '=')
			return (1);
		i++;
	}
	return (-1);
}

int			sh_builtin_unsetenv(char **com)
{
	int		i;

	i = 1;
	if (com[i] == NULL)
	{
		ft_dprintf(STDERR_FILENO, "unsetenv: not enough arguments\n");
		ft_dprintf(STDERR_FILENO, "usage: unsetenv [NAME] ...\n");
		return (ft_free_tab(com));
	}
	while (com[i] != NULL)
	{
		if (unsetenv_find_var(com[i]) < 0)
			ft_dprintf(STDERR_FILENO,
					"unsetenv: variable name unknown: %s\n", com[i]);
		else
			sh_rm_var_env(com[i]);
		i++;
	}
	return (ft_free_tab(com));
}
