/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   histo_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 17:26:31 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/16 11:48:00 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_hist	*create_new_hist(t_hist *a, t_hist *buf)
{
	t_hist	*new;

	if ((new = (t_hist*)malloc(sizeof(t_hist))) == NULL)
		return (NULL);
	new->begin = copy_tline(buf->begin);
	new->next = NULL;
	new->prev = a;
	if (a != NULL)
	{
		new->nb = a->nb + 1;
		a->next = new;
	}
	else
		new->nb = 0;
	return (new);
}

t_hist			*copy_hist(t_hist *historique, t_line *current_line)
{
	t_hist		*buf;
	t_hist		*a;

	buf = historique;
	if ((a = (t_hist*)malloc(sizeof(t_hist))) == NULL)
		return (NULL);
	a->begin = copy_tline(current_line);
	a->next = NULL;
	a->prev = NULL;
	a->nb = 0;
	a = create_new_hist(a, buf);
	while (buf->next != NULL)
	{
		buf = buf->next;
		a = create_new_hist(a, buf);
	}
	while (a->prev)
		a = a->prev;
	return (a);
}
