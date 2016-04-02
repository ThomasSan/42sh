/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 10:02:21 by dbaldy            #+#    #+#             */
/*   Updated: 2016/04/02 16:42:05 by dbaldy           ###   ########.fr       */
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

static int			init_compl(t_param *debut, char *word)
{
	if ((g_curr_compl = (t_compl*)malloc(sizeof(t_compl))) == NULL)
		return (-1);
	g_curr_compl->debut = debut;
	g_curr_compl->var = ft_strdup(word);
	return (0);
}

static int			not_enough_room(t_line_list *first, t_param *debut)
{
	int		size_list;

	print_lines(1);
	size_list = get_size_list(debut);
	ft_dprintf(STDERR_FILENO, "not enough room to print %d solutions", size_list);
	ft_notputs("cr", 1);
	go_back_to_selected_char(first);
	return (0);
}

int					tab_select(t_param **debut, t_line_list **first, char *word)
{
	int		ret;
	char	*param;
	t_param	*list;

	param = (g_curr_compl == NULL) ? word : g_curr_compl->var;
	list = (g_curr_compl == NULL) ? *debut : g_curr_compl->debut;
	if (g_curr_compl != NULL)
		clear_tparam(debut);
	if ((ret = tab_complete_line(list, first, param)) == 0 &&
			g_curr_compl == NULL)
			clear_tparam(debut);
	else if (ret == 1)
	{
		ft_notputs("vi", 1);
		place_cursor_to_completion(*first);
		if (init_compl(*debut, word) == 0 && print_args(list) == 0)
			go_back_to_selected_char(*first);
		else
			not_enough_room(*first, *debut);
		ft_notputs("ve", 1);
	}
	return (0);
}
