/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 10:02:21 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/21 19:09:44 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include "shell.h"

static t_param		*print_col(t_param *buf, int nb_row, int col_nb, int nb_tab)
{
	int		row;

	row = 0;
	while (row < nb_row)
	{
		ft_dprintf(STDIN_FILENO, "%s", buf->var);
		buf = buf->next;
		if (buf->nb == 0)
		{
			go_to_origin(row);
			break ;
		}
		move_cursor_one_down(nb_tab, col_nb);
		row++;
	}
	return (buf);
}

static int			print_args(t_param *debut)
{
	int			col;
	t_param		*buf;
	int			nb_col;
	int			nb_row;

	buf = debut;
	col = 0;
	nb_col = get_nb_col(debut);
	nb_row = get_nb_row(debut, nb_col);
	if (nb_row >= get_height())
		return (-2);
	if (print_lines(nb_row) == -1)
		return (-1);
	while (col < nb_col)
	{
		if ((buf = print_col(buf, nb_row, col, get_nb_tab(debut))) == NULL)
			return (-2);
		if (buf->nb == 0)
			break ;
		if (move_cursor_up(nb_row, get_nb_tab(debut)) < 0)
			return (-1);
		col++;
	}
	return (0);
}

static int			complete_line(char *var, t_com_list *begin)
{
	int			i;
	t_com_list	*new;

	i = g_local->prompt + 1;
	while (i < g_local->curs)
	{
		i++;
		begin = begin->next;
	}
	while (*var)
	{
		ft_dprintf(STDIN_FILENO, "%c", *var);
		new = com_list_new(*var);
		com_list_add(&begin, new);
		var++;
	}
	return (0);
}

int					tab_select(t_param *debut, t_com_list *begin)
{
	if (debut->next == NULL)
		complete_line(debut->var, begin);
	else
	{
		ft_notputs("vi", 1);
		print_args(debut);
		ft_notputs("ve", 1);
	}
	return (0);
}
