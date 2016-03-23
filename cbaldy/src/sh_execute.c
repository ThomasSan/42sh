/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 19:17:28 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/22 19:39:32 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_builtin	g_list_builtin[] = {
	{"cd", &sh_builtin_cd},
	{"env", &sh_builtin_env},
	{"hash", &sh_builtin_hash},
	{"exit", &sh_builtin_exit},
	{"setenv", &sh_builtin_setenv},
	{"unsetenv", &sh_builtin_unsetenv},
};

static int	sh_error_msg(char **com, int error)
{
	int		fd;

	fd = STDERR_FILENO;
	if (error == 2)
		ft_dprintf(STDIN_FILENO, "\n");
	if (error == 11)
		ft_dprintf(fd, "shell: segmentation fault  %s\n", com[0]);
	return (0);
}

int			sh_execute(char **com)
{
	int		i;

	i = 0;
	while (i < 5 && com[0] != NULL)
	{
		if (ft_strncmp(com[0], g_list_builtin[i].name,
					ft_strlen(g_list_builtin[i].name)) == 0 &&
				com[0][ft_strlen(g_list_builtin[i].name)] == '\0')
			return (g_list_builtin[i].f(com));
		i++;
	}
	if (com[0] != NULL)
		i = sh_command(com);
	if (i != 0)
		sh_error_msg(com, i);
	ft_free_tab(com);
	return (0);
}
