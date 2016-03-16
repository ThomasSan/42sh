/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 11:28:06 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/16 10:05:42 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int				clear_thist(t_hist **debut)
{
	t_hist	*a;
	t_hist	*buf;

	buf = *debut;
	if (buf->prev != NULL)
		buf->prev->next = NULL;
	while (buf)
	{
		a = buf->next;
		clear_tline(&(buf->begin));
		buf->next = NULL;
		buf->prev = NULL;
		free(buf);
		buf = a;
	}
	return (0);
}

int				update_list(t_hist **historique, t_line *current_line)
{
	t_hist	*buf;

	if (current_line->next == NULL && current_line->prev == NULL)
		return (0);
	if ((buf = (t_hist*)malloc(sizeof(t_hist))) == NULL)
		return (-1);
	buf->next = *historique;
	buf->prev = NULL;
	select_end(current_line);
	buf->begin = copy_tline(current_line);
	buf->nb = 0;
	(*historique)->prev = buf;
	*historique = buf;
	buf = buf->next;
	while (buf->next)
	{
		buf->nb += 1;
		buf = buf->next;
	}
	buf->nb += 1;
	if (buf->begin->next == NULL)
		clear_thist(&buf);
	return (0);
}

static t_line	*create_new_elem(t_line *a, t_line *buf)
{
	t_line		*new;

	if ((new = (t_line*)malloc(sizeof(t_line))) == NULL)
		return (NULL);
	new->c = buf->c;
	new->select = buf->select;
	new->prev = a;
	new->nb = buf->nb;
	if (buf->next)
		new->next = create_new_elem(new, buf->next);
	else
		new->next = NULL;
	return (new);
}

t_line			*copy_tline(t_line *begin)
{
	t_line		*a;

	if ((a = (t_line*)malloc(sizeof(t_line))) == NULL)
		return (NULL);
	a->prev = NULL;
	a->c = begin->c;
	a->select = begin->select;
	a->nb = begin->nb;
	if (begin->next)
		a->next = create_new_elem(a, begin->next);
	else
		a->next = NULL;
	while (a->prev)
		a = a->prev;
	return (a);
}

int				line_of_command(t_line *debut, char **str)
{
	t_line	*buf;
	int		size;
	char	*ret;
	int		i;

	i = 0;
	size = 0;
	buf = debut;
	while (buf)
	{
		buf = buf->next;
		size++;
	}
	if ((ret = (char*)malloc(sizeof(char) * (size + 1))) == NULL)
		return (-1);
	buf = debut;
	while (buf)
	{
		ret[i] = buf->c;
		i++;
		buf = buf->next;
	}
	ret[i] = '\0';
	*str = ret;
	return (0);
}
