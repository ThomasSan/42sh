/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_mv_cursor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 11:42:12 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/30 20:52:25 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*static int	term_mv_home_end(int move, int len_list)
{
	int		k;

	if (move == 72)
		k = 4;
	else
		k = 3;
	while (term_mv_horizontal(k, len_list) == 0)
		;
	return (0);
}*/

/*static int	term_mv_word(int move, t_com_list *begin, int len_list)
{
	int		i;

	i = g_local->prompt;
	while (i++ != g_local->curs - 1)
		begin = begin->next;
	if (move == 67)
	{
		while (begin && begin->c > 32 && term_mv_horizontal(3, len_list) == 0)
			begin = begin->next;
		while (begin && begin->c < 33 && term_mv_horizontal(3, len_list) == 0)
			begin = begin->next;
	}
	else if (move == 68)
	{
		while (begin && begin->c > 32 && term_mv_horizontal(4, len_list) == 0)
			begin = begin->previous;
		while (begin && begin->c < 33 && term_mv_horizontal(4, len_list) == 0)
			begin = begin->previous;
		if (begin == NULL)
			term_mv_horizontal(4, len_list);
	}
	return (0);
}*/

/*static int	term_mv_vertical(int move, )
{
	int		buf;
	int		line;

	line = g_local->curs / (g_local->nb_col + 1);
	buf 	= g_local->nb_col - 1;
	if (move == 65 && line != 0)
	{
		while (term_mv_horizontal(4, 0) == 0 && buf > 0)
			buf--;
	}
	else if (move == 66 && line < ((len_list + g_local->prompt) /
				(g_local->nb_col + 1)))
	{
		while (term_mv_horizontal(3, len_list) == 0 && buf > 0)
			buf--;
	}
	else
		return (-1);
	return (0);
}*/

int		term_mv_cursor(char buf, t_line_list **first)
{
	/*if (buf == 70 || buf == 72)
		return (term_mv_home_end(buf, len_list));
	else if (buf == 65 || buf == 66)
		term_mv_vertical(buf, len_list);
	else if (buf == 67 || buf == 68)
		term_mv_word(buf, begin, len_list);*/
	return (0);
	buf = 0;
	*first = NULL;
}
