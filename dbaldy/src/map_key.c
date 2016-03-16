/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_line_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/27 17:15:46 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/14 18:06:15 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	increase_nb(t_line *buf)
{
	while (buf)
	{
		buf->nb += 1;
		buf = buf->next;
	}
	return (0);
}

static int	new_char_chaine(char n_c, t_line **chaine)
{
	t_line		*new;
	t_line		*buf;

	buf = *chaine;
	if ((new = (t_line*)malloc(sizeof(t_line))) == NULL)
		return (-1);
	while (buf->next && buf->select == 0)
		buf = buf->next;
	new->c = n_c;
	new->select = 0;
	new->next = buf;
	new->prev = buf->prev;
	buf->prev = new;
	new->nb = buf->nb;
	increase_nb(buf);
	if (new->prev != NULL)
		new->prev->next = new;
	*chaine = ((*chaine)->select == 1) ? new : *chaine;
	line_to_print(new);
	return (0);
}

static int	move_cursor_chaine(char direction, t_line **chaine)
{
	t_line		*buf;

	buf = *chaine;
	while (buf && buf->select == 0)
		buf = buf->next;
	buf->select -= 1;
	if (direction == 67 && buf->next != NULL)
		buf->next->select += 1;
	else if (direction == 68 && buf->prev != NULL)
		buf->prev->select += 1;
	else
		buf->select += 1;
	move_cursor(direction, buf);
	return (0);
}

int			map_key(char *buf, t_hist **historique, t_line **current_line)
{
	if (buf[0] >= 32 && buf[0] < 127 && buf[1] == '\0')
		return (new_char_chaine(buf[0], current_line));
	else if (buf[0] == 27 && buf[1] == 91 && (buf[2] == 66 || buf[2] == 65) &&
			buf[3] == '\0')
		return (change_hist(buf[2], historique, current_line));
	else if (buf[0] == 27 && buf[1] == 91 && (buf[2] == 67 || buf[2] == 68) &&
			buf[3] == '\0')
		return (move_cursor_chaine(buf[2], current_line));
	else if ((buf[0] == 8 || buf[0] == 127) && buf[1] == 0)
		return (suppr_char_list(current_line));
	else if (buf[0] == 27 && buf[1] == 91 && (buf[2] == 70) &&
			buf[3] == '\0')
		go_end(*current_line);
	else if (buf[0] == 27 && buf[1] == 91 && (buf[2] == 72) &&
			buf[3] == '\0')
		go_home(*current_line);
	return (0);
}
