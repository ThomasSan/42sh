/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_static.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/23 12:38:16 by cbaldy            #+#    #+#             */
/*   Updated: 2016/04/23 15:02:19 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		non_empty(t_line_list *first)
{
	char	*buf;
	int		i;

	while (first->previous)
		first = first->previous;
	i = 0;
	buf = line_list_retrieve(first);
	while (buf[i])
	{
		if (buf[i] != ' ' && buf[i] != '\0')
		{
			free(buf);
			return (0);
		}
		i++;
	}
	free(buf);
	return (1);
}

static int		new_elem_hist(t_hist_list *hist, t_line_list *first)
{
	t_line_list	*tmp;

	tmp = first;
	while (tmp->next)
		tmp = tmp->next;
	while (tmp->previous)
	{
		tmp->marge = 0;
		tmp = tmp->previous;
	}
	hist->old = line_list_dup(tmp);
	return (0);
}

t_hist_list		*retrieve_history(int flag, t_line_list *first)
{
	static t_hist_list	*hist;
	t_hist_list			*buf;

	buf = NULL;
	if (flag == 0)
	{
		hist_list_new(&buf);
		buf->next = copy_hist(hist);
		if (buf->next != NULL)
			buf->next->previous = buf;
		return (buf);
	}
	else if (flag == 2)
		return (copy_hist(hist));
	else if (non_empty(first) == 0)
	{
		hist_list_new(&hist);
		new_elem_hist(hist, first);
	}
	return (NULL);
}
