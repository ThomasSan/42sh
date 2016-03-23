/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 10:02:21 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/23 15:23:47 by cbaldy           ###   ########.fr       */
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

int					tab_select(t_param *debut, t_com_list *begin)
{
	return (0);
	debut = NULL;
	begin = NULL;
	print_args(debut);	
//	if (tab_complete_line(debut, begin, word) == 0)
//		return (0);
//	else
//	{
/*	if (tab_complete_line(debut, begin, word) == 0)
		return (0);
	else
	{
>>>>>>> 3696930128184ee1317685dc07a5bc25cfbfb316
		ft_notputs("vi", 1);
		g_local->completion = 1;
		place_cursor_to_completion(begin);
		print_args(debut);
		go_back_to_selected_char(begin);
		ft_notputs("ve", 1);
<<<<<<< HEAD
//	}
	return (0);
=======
	}
	return (0);*/
}
