/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 14:33:24 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/15 11:42:27 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int			get_fd(int type)
{
	static int		*buf;

	if (type == 1)
	{
		close(buf[0]);
		free(buf);
		buf = NULL;
		return (0);
	}
	if (buf == NULL)
	{
		buf = (int*)malloc(sizeof(int) * 1);
		buf[0] = open("/dev/tty", O_RDWR);
	}
	return (buf[0]);
}

void		clear_list(t_param **debut)
{
	t_param		*buf;
	t_param		*a;

	buf = (*debut)->next;
	a = buf->next;
	while (buf->nb > 0)
	{
		free(buf->var);
		buf->next = NULL;
		buf->prev = NULL;
		free(buf);
		buf = a;
		a = (buf != NULL) ? buf->next : NULL;
	}
	free(*debut);
}

void		reset_term(void)
{
	struct termios		term;

	ft_tputs("cr", 1);
	ft_tputs("cd", 1);
	tcgetattr(0, &term);
	ft_tputs("ve", 1);
	term.c_lflag |= (ICANON | ECHO);
	tcsetattr(0, TCSADRAIN, &term);
}

int			fputchar(int c)
{
	ft_putchar_fd(c, get_fd(0));
	return (0);
}
