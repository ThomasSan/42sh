/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suppr_elem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 13:59:00 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/15 11:32:14 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int			decrease_nb(t_line *buf)
{
	while (buf)
	{
		buf->nb -= 1;
		buf = buf->next;
	}
	return (0);
}

static int			suppr_char(t_line *buf)
{
	ft_tputs("dm", 1);
	ft_tputs("dc", 1);
	ft_tputs("ed", 1);
	if (buf->next != NULL)
		line_to_print(buf);
	if (buf->next != NULL)
		ft_tputs("le", 1);
	return (0);
}

int					suppr_char_list(t_line **chaine)
{
	t_line		*buf;

	buf = *chaine;
	if (buf->select == 1 && buf->prev == NULL)
		return (0);
	while (buf && buf->next && buf->next->select == 0)
		buf = buf->next;
	move_cursor(68, buf->next);
	decrease_nb(buf->next);
	if (buf->prev == NULL)
	{
		*chaine = buf->next;
		(*chaine)->prev = NULL;
		suppr_char(*chaine);
	}
	else
	{
		buf->prev->next = buf->next;
		buf->next->prev = buf->prev;
		suppr_char(buf->next);
	}
	free(buf);
	return (0);
}
