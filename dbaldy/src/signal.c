/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 16:49:16 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/15 11:28:38 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void		handle_sigwinch(void)
{
	ft_tputs("cl", 1);
	if (print_args(g_debut) == -2)
	{
		ft_tputs("cl", 1);
		ft_dprintf(STDERR_FILENO, "\x1b[31;01mSCREEN SIZE TOO SMALL\x1b[0;m");
	}
}

static void		handle_sigtstp(void)
{
	struct termios	term;
	char			cp[2];

	tcgetattr(get_fd(0), &term);
	cp[0] = term.c_cc[VSUSP];
	cp[1] = 0;
	reset_term();
	get_fd(1);
	signal(SIGTERM, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	ioctl(get_fd(0), TIOCSTI, cp);
}

static void		handle_sigcont(void)
{
	signal(SIGTSTP, sig_handler);
	signal(SIGINT, sig_handler);
	signal(SIGTERM, sig_handler);
	init_term();
	ft_tputs("vi", 1);
	if (print_args(g_debut) == -2)
	{
		ft_tputs("cl", 1);
		ft_dprintf(STDERR_FILENO, "\x1b[31;01mSCREEN SIZE TOO SMALL\x1b[0;m");
	}
}

static void		handle_sigkill(void)
{
	reset_term();
	get_fd(1);
	clear_list(&g_debut);
	exit(1);
}

void			sig_handler(int sig)
{
	if (sig == SIGTSTP)
		handle_sigtstp();
	if (sig == SIGCONT)
		handle_sigcont();
	if (sig == SIGWINCH)
		handle_sigwinch();
	if (sig == SIGINT || sig == SIGTERM)
		handle_sigkill();
}
