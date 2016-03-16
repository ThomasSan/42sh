/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 10:16:17 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/14 18:03:23 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			return_to_prompt(t_line *debut)
{
	t_line	*buf;
	int		size;
	int		nb;

	size = 0;
	buf = debut;
	while (buf && buf->select == 0)
	{
		size++;
		buf = buf->next;
	}
	nb = ((int)ft_strlen(g_prompt) + size) / get_width();
	ft_tputs("up", nb);
	ft_tputs("cr", 1);
	nb = (int)ft_strlen(g_prompt);
	ft_tputs("nd", nb);
	return (0);
}

int			print_line(t_line *debut)
{
	t_line	*buf;

	buf = debut;
	while (buf)
	{
		ft_dprintf(get_fd(0), "%c", buf->c);
		buf = buf->next;
	}
	return (0);
}

int			clear_tline(t_line **elem)
{
	t_line	*buf;
	t_line	*a;

	buf = *elem;
	if (buf->prev != NULL)
		buf->prev->next = NULL;
	while (buf)
	{
		a = buf->next;
		buf->next = NULL;
		buf->prev = NULL;
		free(buf);
		buf = a;
	}
	return (0);
}

int			select_end(t_line *current_line)
{
	t_line	*buf;

	buf = current_line;
	while (buf->next)
	{
		buf->select = 0;
		buf = buf->next;
	}
	buf->select = 1;
	return (0);
}

int			change_hist(char direction, t_hist **historique,
		t_line **current_line)
{
	return_to_prompt(*current_line);
	if (direction == 66 && (*historique)->prev != NULL)
	{
		select_end(*current_line);
		clear_tline(current_line);
		*current_line = copy_tline((*historique)->prev->begin);
		*historique = (*historique)->prev;
	}
	if (direction == 65 && (*historique)->next != NULL)
	{
		select_end(*current_line);
		if ((*historique)->prev == NULL)
		{
			clear_tline(&((*historique)->begin));
			(*historique)->begin = copy_tline(*current_line);
		}
		clear_tline(current_line);
		*current_line = copy_tline((*historique)->next->begin);
		*historique = (*historique)->next;
	}
	print_line(*current_line);
	ft_tputs("le", 1);
	ft_tputs("cd", 1);
	return (0);
}
