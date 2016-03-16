/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_edit_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 12:51:22 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/16 12:08:07 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	term_len_1(char buf)
{
	if (buf == 28)
	{
		ft_free_tab(g_env);
		sh_reset_term();
		ft_dprintf(STDOUT_FILENO, "\t21sh: exit\n");
		exit(0);
	}
	if (buf == 3)
	{
		ft_dprintf(STDOUT_FILENO, "\n");
		return (3);
	}
	if (buf == 4)
		return (4);
	return (0);
}

static int	term_len_3(char buf, t_com_list **begin, t_hist_list **hist)
{
	if (buf == 65 || buf == 66)
		return (hist_change(buf - 64, hist, begin));
	if (buf == 67 || buf == 68)
		term_mv_horizontal(buf - 64, com_list_count(*begin));
	if (buf == 70 || buf == 72)
		return (term_mv_cursor(buf, com_list_count(*begin), *begin));
	return (0);	
}

int			term_edit_line(char *buf, int len, t_com_list **begin,
		t_hist_list **hist)
{
	if (len == 1)
		return (term_len_1(buf[0]));
	if (len == 3 && buf[0] == 27 && buf[1] == 91)
		term_len_3(buf[2], begin, hist);
	else if (len == 6 && buf[0] == 27 && buf[1] == 91 && buf[2] == 49 && buf[3]
			== 59 && buf[4] == 50)
	{
		if (buf[5] == 65 || buf[5] == 66)
			term_mv_cursor(buf[5], com_list_count(*begin), *begin);
		else if (buf[5] == 67 || buf[5] == 68)
			term_mv_cursor(buf[5], com_list_count(*begin), *begin);
	}
	else if (len == 2 && buf[0] == -61 && buf[1] == -89)
		copy_cut_mode(begin, 1);
	else if (len == 3 && buf[0] == -30 && buf[1] == -120 && buf[2] == -102)
		copy_paste(begin);
	else if (len == 3 && buf[0] == -30 && buf[1] == -119 && buf[2] == -120)
		copy_cut_mode(begin, 2);
	return (buf[0]);
}
