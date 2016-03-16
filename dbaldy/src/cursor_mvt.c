/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_mvt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 15:53:13 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/15 11:42:50 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int			print_lines(int nb_row)
{
	ft_tputs("sf", nb_row);
	ft_tputs("up", nb_row);
	return (0);
}

int			move_cursor_one_down(int nb_tab, int col_nb)
{
	int		col;

	col = 0;
	ft_tputs("do", 1);
	while (col < col_nb)
	{
		ft_tputs("ta", nb_tab);
		col++;
	}
	return (0);
}

int			move_cursor_up(int nb_row, int nb_tab)
{
	ft_tputs("up", nb_row);
	ft_tputs("ta", nb_tab);
	return (0);
}

void		go_to_origin(int row)
{
	char	buf[30];
	char	*ap;
	char	*go_up;
	char	*carriage;

	ap = buf;
	carriage = tgetstr("cr", &ap);
	tputs(carriage, 1, fputchar);
	go_up = tgetstr("up", &ap);
	while (row-- > 0)
		tputs(go_up, 1, fputchar);
}

int			ft_tputs(char *mvt, int nb_occ)
{
	char	buf[30];
	char	*ap;
	char	*my_mvt;

	ap = buf;
	my_mvt = tgetstr(mvt, &ap);
	while (nb_occ-- > 0)
		tputs(my_mvt, 1, fputchar);
	return (0);
}
