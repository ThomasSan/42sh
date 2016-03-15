/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 12:36:46 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/09 16:10:15 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			main(int ac, char **av, char **env)
{
	if (ac != 1)
	{
		ft_dprintf(STDERR_FILENO, "shell: argument invalid: %s\n", av[1]);
		return (0);
	}
	sh_set_env(env);
	sh_set_term();
	signal(SIGQUIT, signal_handler);
	while (42)
	{
		if (sh_prompt() < 0)
		{
			ft_free_tab(g_env);
			sh_reset_term();
			return (0);
		}
	}
	return (0);
}
