/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_write_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 12:47:39 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/31 16:22:25 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	ed_add_char(t_line_list **first, char buf)
{
	t_com_list	*new;

	if ((new = com_list_new(buf)) == NULL)
		return (-1);
	com_list_add(&((*first)->begin), new, (*first)->marge);
	print_command(new, buf, *first);
	return (buf);
}

static int	ed_delete_char(t_line_list **first)
{
	t_com_list	*tmp;
	int			i;

	if ((*first)->marge > 0)
	{
		i = 0;
		tmp = (*first)->begin;
		if (g_local->curs == (*first)->marge + 1 ||
				com_list_count((*first)->begin) == 0)
			return (0);
		while (tmp->next != NULL && i < g_local->curs - (*first)->marge - 2)
		{
			tmp = tmp->next;
			i++;
		}
		print_command(tmp->next, 127, *first);
		com_list_remove(tmp, &((*first)->begin));
	}
	return (0);
}

static int	ed_finish_line(t_line_list **first)
{
	int			i;
	int			k;
	t_line_list	*second;

	k = com_list_count((*first)->begin);
	while (term_mv_horizontal(3, first) != -1)
		;
	if ((i = term_finish_line(*first)) < 0)
	{
		ed_add_char(first, '\n');
		second = line_list_new(ft_dprintf(STDIN_FILENO, "new_line> "));
		second->previous = *first;
		(*first)->next = second;
		*first = second;
		g_local->curs = 11;
		return (0);
	}
	ft_putchar('\n');
	return (10);
}

int			term_write_line(t_line_list **first, char buf)
{
	if (buf == 127)
		return (ed_delete_char(first));
	else if (buf == 10)
		return (ed_finish_line(first));
	else if (buf > 31 && buf < 127)
		return (ed_add_char(first, buf));
	return (0);
}
