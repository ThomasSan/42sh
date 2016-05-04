/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_ctrld_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 10:40:18 by cbaldy            #+#    #+#             */
/*   Updated: 2016/05/03 12:06:06 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	ed_delete_char_nl(t_line_list **first)
{
	t_com_list	*tmp;
	t_line_list	*buf[2];

	buf[0] = (*first)->previous;
	buf[1] = (*first)->next;
	tmp = buf[0]->begin;
	while (tmp->next != NULL)
		tmp = tmp->next;
	term_mv_horizontal(4, first, 0);
	ft_tputs("cd", 1, 0);
	(*first) = (*first)->next;
	tmp->next = (*first)->begin;
	if ((*first)->begin != NULL)
		(*first)->begin->previous = tmp;
	free(*first);
	buf[0]->next = buf[1];
	if (buf[1] != NULL)
		buf[1]->previous = buf[0];
	*first = buf[0];
	print_command(tmp->next, 0, *first);
	if (tmp->next != NULL)
		term_mv_horizontal(4, first, 0);
	com_list_remove(tmp, &(buf[0]->begin));
	return (0);
}

int			ed_ctrld_line(t_line_list **first)
{
	t_com_list	*tmp;
	int			i;

	if ((*first)->begin == NULL && (*first)->previous == NULL)
		return (4);
	if (term_mv_horizontal(3, first, 0) < 0)
		return (0);
	if (g_local->curs == 1 && (*first)->previous != NULL)
		return (ed_delete_char_nl(first));
	if ((g_local->curs == (*first)->marge + 1 && (*first)->marge > 0) ||
			com_list_count((*first)->begin) == 0)
		return (0);
	i = 0;
	tmp = (*first)->begin;
	while (tmp->next != NULL && i < g_local->curs - (*first)->marge - 2)
	{
		tmp = tmp->next;
		i++;
	}
	print_command(tmp->next, 127, *first);
	com_list_remove(tmp, &((*first)->begin));
	return (0);
}
