/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_setenv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 14:01:52 by cbaldy            #+#    #+#             */
/*   Updated: 2016/05/02 10:17:49 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	setenv_is_valid(char *str)
{
	int		i[2];

	i[0] = 0;
	i[1] = 0;
	if ((str[i[0]] >= '0' && str[i[0]] <= '9') || str[i[0]] == '=')
		return (-1);
	while (str[i[0]] != '\0' && str[i[0]] != '=')
	{
		if ((str[i[0]] < '0' || str[i[0]] > '9') && (str[i[0]] < 'A' ||
				str[i[0]] > 'Z') && str[i[0]] != '_')
			return (-1);
		i[0]++;
	}
	if (str[i[0]] != '=')
		return (-1);
	return (1);
}

static int	setenv_check_arg(char **com)
{
	int		i[2];

	i[1] = 1;
	while (com[i[1]] != NULL)
		i[1]++;
	if (i[1] == 1)
		return (-1);
	i[0] = 1;
	while (i[0] < i[1])
	{
		if (setenv_is_valid(com[i[0]]) < 0)
			return (-ft_dprintf(STDERR_FILENO,
						"setenv: invalid variable name: %s\n", com[i[0]]));
			i[0]++;
	}
	return (i[1]);
}

static char	*setenv_get_varname(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	return (ft_strsub(str, 0, i));
}

int			sh_builtin_setenv(char **com)
{
	int		i[2];
	char	*name;

	if ((i[0] = setenv_check_arg(com)) < 0)
	{
		ft_dprintf(STDERR_FILENO, "usage: setenv [NAME]=[VALUE] ... \n");
		return (1);
	}
	i[1] = 1;
	while (i[1] < i[0])
	{
		name = setenv_get_varname(com[i[1]]);
		if (sh_change_var_env(name, &(ft_strchr(com[i[1]], '=')[1])) == -1)
			sh_add_var_env(name, &(ft_strchr(com[i[1]], '=')[1]));
		i[1]++;
		free(name);
	}
	return (0);
}
