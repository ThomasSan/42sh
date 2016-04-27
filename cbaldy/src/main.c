/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 12:36:46 by cbaldy            #+#    #+#             */
/*   Updated: 2016/04/27 17:26:38 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	main_alt(void)
{
	sh_reset_term();
	ft_putstr_fd("shell: no termcaps activated\n", STDOUT_FILENO);
	ft_putstr_fd("TERM not found or unknown\n", STDOUT_FILENO);
	ft_putstr_fd("WARNING: undetermined behaviors may occur\n", STDOUT_FILENO);
	while (42)
	{
		if (sh_minishell() < 0)
		{
			ft_free_tab(g_env);
			sh_reset_term();
			return (0);
		}
	}
	return (0);
}

int			main(int ac, char **av, char **env)
{
	if (ac != 1)
	{
		ft_dprintf(STDERR_FILENO, "shell: argument invalid: %s\n", av[1]);
		return (0);
	}
	sh_set_env(env);
	
	int	i = 0;
	int	j = 0;
	if ((j = sh_get_term_fildes()) < 0 || (i = sh_set_term() < 0))
	{
		printf("%d %d\n", j, i);
		return (main_alt());
	}
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
