/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_signal_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 12:43:45 by cbaldy            #+#    #+#             */
/*   Updated: 2016/04/24 17:17:20 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		sig_quit(void)
{
	ft_free_tab(g_env);
	sh_reset_term();
	ft_dprintf(STDOUT_FILENO, "\t21sh: exit\n");
	exit(g_local->exit_value);
}

void		sig_int(void)
{
	char	buf;

	buf = 4;
	ft_dprintf(STDIN_FILENO, "%c", buf);
}

void		signal_handler(int signum)
{
	if (signum == SIGQUIT)
		sig_quit();
	if (signum == SIGINT)
		sig_int();
}
