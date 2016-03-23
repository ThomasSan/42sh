/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_write_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 12:47:39 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/23 11:33:22 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	ed_add_char(t_com_list **begin, char buf)
{
	t_com_list	*new;

	if ((new = com_list_new(buf)) == NULL)
		return (-1);
	com_list_add(begin, new);
	print_command(new, buf);
	return (buf);
}

static int	ed_delete_char(t_com_list **begin)
{
	t_com_list	*tmp;
	int			i;

	i = 0;
	tmp = *begin;
	if (g_local->curs == g_local->prompt + 1 || com_list_count(*begin) == 0)
		return (0);
	while (tmp->next != NULL && i < g_local->curs - g_local->prompt - 2)
	{
		tmp = tmp->next;
		i++;
	}
	print_command(tmp->next, 127);
	com_list_remove(tmp, begin);
	return (0);
}

static int	ed_save_line(t_com_list **begin)
{
	t_com_list	*tmp;

	tmp = g_local->begin;
	if (tmp == NULL)
		g_local->begin = *begin;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = *begin;
		(*begin)->previous = tmp;
	}
	*begin = NULL;
	return (0);
}

static int	ed_finish_line(t_com_list **begin)
{
	int		i;

	if ((i = lex_finish_line(*begin)) < 0)
		ed_add_char(begin, ' ');
	if (i < 0)
	{
		ft_dprintf(STDIN_FILENO, "\nline>");
		g_local->prompt = 5;
		g_local->curs = g_local->prompt + 1;
		ed_save_line(begin);
		return (0);
	}
	ft_dprintf(STDIN_FILENO, "\n");
	return (10);
}

int			term_write_line(t_com_list **begin, char buf)
{
	if (buf == 127)
		return (ed_delete_char(begin));
	else if (buf == 10)
		return (ed_finish_line(begin));
	else if (buf > 31 && buf < 127)
		return (ed_add_char(begin, buf));
	return (0);
}
