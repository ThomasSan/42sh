/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_unsetenv.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 11:38:34 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/24 16:11:05 by cbaldy           ###   ########.fr       */
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
	int		ret;

	i = 1;
	ret = 0;
	if (com[i] == NULL)
	{
		ft_dprintf(STDERR_FILENO, 
				"unsetenv: not enough args\nusage: unsetenv [NAME] ...\n");
		return (1);
	}
	while (com[i] != NULL)
	{
		if (unsetenv_find_var(com[i]) < 0)
			ret = ft_dprintf(STDERR_FILENO,
					"unsetenv: variable name unknown: %s\n", com[i]);
		else
			sh_rm_var_env(com[i]);
		i++;
	}
	if (ret != 0)
		return (1);
	return (0);
}
