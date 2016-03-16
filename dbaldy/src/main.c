/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/27 16:22:20 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/15 11:43:25 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "shell.h"

int					main(int ac, char **av, char **env)
{
	char	buf[2048];

	getenv("TERM");
	ft_tputs("vi", 1);
	tgetent(buf, getenv("TERM"));
	g_env = get_env(env, av[0]);
	shell_level(g_env);
	g_prompt = ft_strdup("$> ");
	g_print_ch = NULL;
	g_ret = 0;
	init_term();
	while (get_prompt() == 0)
		init_term();
	return (g_ret);
	ac = 0;
}
