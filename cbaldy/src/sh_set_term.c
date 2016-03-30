/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_set_term.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 09:45:00 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/29 18:34:19 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			sh_get_term_fildes(void)
{
	char	*term;
	int		i;

	if ((i = sh_is_new_var("TERM")) < 0)
	{
		g_local->le_mode = 1;
		return (-1);
	}
	term = &(ft_strchr(g_env[i], '=')[1]);
	if (tgetent(NULL, term) != 1)
	{
		g_local->le_mode = 1;
		return (-1);
	}
	return (0);
}

int			sh_set_term(void)
{
	struct termios	tmp;

	if (tcgetattr(STDIN_FILENO, &tmp) < 0)
		return (-1);
	tmp.c_cc[VMIN] = 1;
	tmp.c_cc[VTIME] = 0;
	tmp.c_lflag &= ~(ICANON | ECHO | ISIG);
	if ((tcsetattr(STDIN_FILENO, TCSANOW, &tmp)) < 0)
		return (-1);
	return (0);
}

int			sh_reset_term(void)
{
	struct termios	tmp;

	if (tcgetattr(STDIN_FILENO, &tmp) < 0)
		return (-1);
	tmp.c_lflag |= (ICANON | ECHO | ISIG);
	if ((tcsetattr(STDIN_FILENO, TCSANOW, &tmp)) < 0)
		return (-1);
	ft_tputs("ve", 1, 0);
	return (0);
}
