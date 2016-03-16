/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 10:02:21 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/15 11:42:02 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int			print_one_arg(t_param *buf)
{
	char	*standout;
	char	buf2[30];
	char	*ap;

	ap = buf2;
	if ((buf->select % 2) == 1 && (standout = tgetstr("us", &ap)) != NULL)
		tputs(standout, 1, fputchar);
	if ((buf->select / 2) == 1 && (standout = tgetstr("so", &ap)) != NULL)
		tputs(standout, 1, fputchar);
	ft_dprintf(get_fd(0), "%s", buf->var);
	if ((buf->select % 2) == 1 && (standout = tgetstr("ue", &ap)) != NULL)
		tputs(standout, 1, fputchar);
	if ((buf->select / 2) == 1 && (standout = tgetstr("se", &ap)) != NULL)
		tputs(standout, 1, fputchar);
	if ((int)ft_strlen(buf->var) > get_width())
		return (-1);
	return (0);
}

static t_param		*print_col(t_param *buf, int nb_row, int col_nb, int nb_tab)
{
	int		row;

	row = 0;
	while (row < nb_row)
	{
		if (print_one_arg(buf) == -1)
			return (NULL);
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

int					print_args(t_param *debut)
{
	int			col;
	t_param		*buf;
	int			nb_col;
	int			nb_row;

	buf = debut;
	col = 0;
	nb_col = get_nb_col(debut);
	nb_row = get_nb_row(debut, nb_col);
	if (nb_row > get_height())
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

int					ft_select(t_param **debut)
{
	char	buf[10];
	int		ret;

	ft_tputs("vi", 1);
	if (print_args(*debut) == -1)
		return (-1);
	if (print_args(*debut) == -2)
	{
		ft_tputs("cl", 1);
		ft_dprintf(STDERR_FILENO, "\x1b[31;01mSCREEN SIZE TOO SMALL\x1b[0;m");
	}
	ret = read(0, buf, 10);
	ft_bzero(&buf[ret], 10 - ret);
	return (read_key(buf, debut));
}
