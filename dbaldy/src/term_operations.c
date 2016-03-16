/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 17:25:16 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/15 11:32:02 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			go_end(t_line *current_line)
{
	t_line	*buf;
	int		gap;

	buf = current_line;
	while (buf && buf->select == 0)
		buf = buf->next;
	if (buf->next == NULL)
		return (0);
	buf->select -= 1;
	while (buf->next)
		buf = buf->next;
	buf->select += 1;
	return_to_prompt(current_line);
	gap = (buf->nb + (int)ft_strlen(g_prompt)) / get_width();
	ft_tputs("sf", gap);
	ft_tputs("do", gap);
	ft_tputs("cr", 1);
	gap = (buf->nb + (int)ft_strlen(g_prompt)) % get_width();
	ft_tputs("nd", gap);
	return (0);
}

int			go_home(t_line *current_line)
{
	t_line		*buf;

	buf = current_line;
	while (buf && buf->select == 0)
		buf = buf->next;
	return_to_prompt(current_line);
	current_line->select += 1;
	buf->select -= 1;
	return (0);
}

int			move_cursor(char direction, t_line *buf)
{
	int		length;

	length = (int)ft_strlen(g_prompt);
	if (direction == 67 && buf->next != NULL)
	{
		if (((length + buf->nb) % (get_width() - 1)) == 0)
		{
			ft_tputs("cr", 1);
			ft_tputs("do", 1);
		}
		else
			ft_tputs("nd", 1);
	}
	else if (direction == 68 && buf->prev != NULL)
	{
		if (((length + buf->nb) % get_width()) == 0)
		{
			ft_tputs("up", 1);
			ft_tputs("nd", get_width() - 1);
		}
		else
			ft_tputs("le", 1);
	}
	return (0);
}
