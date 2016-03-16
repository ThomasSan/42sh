/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 17:49:20 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/03 14:26:45 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int	param_select(t_param *debut)
{
	t_param		*buf;

	buf = debut;
	while ((buf->select % 2) != 1)
		buf = buf->next;
	buf->select = (buf->select / 2 == 1) ? 0 : 2;
	buf->next->select += 1;
	return (0);
}

static int	new_position(char c, int place, int nb_row, int size_list)
{
	if (c == 65)
		return ((place - 1 < 0) ? size_list - 1 : place - 1);
	else if (c == 66)
		return ((place + 1 == size_list) ? 0 : place + 1);
	else if (c == 67)
		return ((place + nb_row > size_list - 1) ? (place % nb_row) :
				place + nb_row);
	else
	{
		if (place - nb_row < 0)
			return (((size_list % nb_row) < place + 1) ? ((size_list / nb_row)
						- 1) * nb_row + place : (size_list / nb_row) *
							nb_row + place);
			return (place - nb_row);
	}
}

static int	reselect(char *buf, t_param *debut, int nb_row)
{
	t_param	*lol;
	int		new_pos;
	int		size_list;

	size_list = get_size_list(debut);
	lol = debut;
	while ((lol->select % 2) == 0)
		lol = lol->next;
	lol->select -= 1;
	new_pos = new_position(buf[2], lol->nb, nb_row, size_list);
	while (lol->nb != new_pos)
		lol = lol->next;
	lol->select += 1;
	return (0);
}

static int	suppr_elem(t_param **debut)
{
	t_param *buf;
	t_param	*lol;

	buf = *debut;
	while ((buf->select % 2) == 0)
		buf = buf->next;
	if (buf->nb == 0 && buf->next->nb == 0)
		return (-1);
	lol = buf->next;
	*debut = (buf->nb == 0) ? lol : *debut;
	g_debut = *debut;
	lol->prev = buf->prev;
	buf->prev->next = lol;
	free(buf->var);
	free(buf);
	lol->select += 1;
	while (lol->nb != 0)
	{
		lol->nb--;
		lol = lol->next;
	}
	ft_tputs("cd", 1);
	lol = (*debut)->next;
	return (0);
}

int			read_key(char *buf, t_param **debut)
{
	int		nb_row;

	nb_row = get_nb_row(*debut, get_nb_col(*debut));
	if (buf[0] == 27 && buf[1] == 91 && buf[2] >= 65 &&
			buf[2] <= 68 && buf[3] == 0)
		reselect(buf, *debut, nb_row);
	else if (buf[0] == 27 && buf[1] == 0)
		return (-1);
	else if (buf[0] == 32 && buf[1] == 0)
		param_select(*debut);
	else if ((buf[0] == 8 || buf[0] == 127) && buf[1] == 0)
		return (suppr_elem(debut));
	else if (buf[0] == 10 && buf[1] == 0)
		return (1);
	return (0);
}
