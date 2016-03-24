/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_setenv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 14:01:52 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/24 17:04:14 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	setenv_check_av(char **com)
{
	int		i;

	i = 0;
	while (com[i] != NULL)
		i++;
	if (i == 1)
		return (-1);
	else if (i < 3)
		return (-ft_dprintf(STDERR_FILENO, "setenv: too few arguments\n"));
	else if (i % 2 != 1)
		return (-ft_dprintf(STDERR_FILENO, "setenv: too many arguments\n"));
	else
		return ((i - 1) / 2);
}

int			sh_builtin_setenv(char **com)
{
	int		i[2];

	if ((i[0] = setenv_check_av(com)) < 0)
	{
		ft_dprintf(STDERR_FILENO, "usage: setenv [NAME] [VALUE] ... \n");
		return (ft_free_tab(com));
	}
	i[1] = 0;
	while (i[1] < i[0])
	{
		if (sh_change_var_env(com[2 * i[1] + 1], com[2 * i[1] + 2]) == -1)
			sh_add_var_env(com[2 * i[1] + 1], com[2 * i[1] + 2]);
		i[1]++;
	}
	return (ft_free_tab(com));
}
