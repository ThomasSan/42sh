/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_write_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/23 16:37:06 by cbaldy            #+#    #+#             */
/*   Updated: 2016/04/23 17:47:12 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	heredoc_add_char(t_line_list **first, char buf)
{
	t_com_list	*new;

	if ((new = com_list_new(buf)) == NULL)
		return (-1);
	com_list_add(&((*first)->begin), new, (*first)->marge);
	print_command(new, buf, *first);
	return (buf);
}

static int	heredoc_delete_char(t_line_list **first)
{
	t_com_list	*tmp;
	int			i;

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

static int	heredoc_finish_line(t_line_list **first, char *eof)
{
	t_line_list	*second;
	char		*str;

	while (term_mv_horizontal(3, first, 0) != -1)
		;
	str = line_list_retrieve(*first);
	if (ft_strcmp(eof, str) != 0)
	{
		heredoc_add_char(first, '\n');
		second = line_list_new(ft_dprintf(STDIN_FILENO, "heredoc> "));
		second->previous = *first;
		(*first)->next = second;
		*first = second;
		g_local->curs = 10;
		free(str);
		return (0);
	}
	free(str);
	ft_putchar_fd('\n', STDIN_FILENO);
	return (10);
}

int			heredoc_write_line(t_line_list **first, char buf, char *eof)
{
	if (buf == 127)
		return (heredoc_delete_char(first));
	else if (buf == 10)
		return (heredoc_finish_line(first, eof));
	else if (buf > 31 && buf < 127)
		return (heredoc_add_char(first, buf));
	return (0);
}
