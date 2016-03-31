/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_edit_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 12:51:22 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/31 15:00:33 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_edit_line	g_edit_line[] = {
	{"\x1c", 1},
	{"\x3", 1},
	{"\x9", 1},
	{"\x4", 1},
	{"\x12", 1},
	{"\x15", 7},
	{"\x0b", 7},
	{"\x19", 7},
	{"\xc3\xa7", 2},
	{"\xe2\x89\x88", 2},
	{"\xe2\x88\x9a", 3},
	{"\x1b[A", 4},
	{"\x1b[B", 4},
	{"\x1b[C", 5},
	{"\x1b[D", 5},
	{"\x1b[F", 6},
	{"\x1b[H", 6},
	{"\x1b[1;2A", 6},
	{"\x1b[1;2B", 6},
	{"\x1b[1;2C", 6},
	{"\x1b[1;2D", 6},
	{NULL, 0},
};

static int	term_spec_char(char buf, t_line_list **first, t_hist_list **hist)
{
	if (buf == 28)
	{
		ft_free_tab(g_env);
		sh_reset_term();
		ft_dprintf(STDOUT_FILENO, "\t21sh: exit\n");
		exit(0);
	}
	if (buf == 3)
		ft_dprintf(STDOUT_FILENO, "\n");
	//if (buf == 9)
	//	return (tab_mode((*first)->begin);
	//if (buf == 18)
	//	return (manage_search_hist("", (*first)->begin, hist, 0));
	return (buf);
	*hist = NULL;
	*first = NULL;
}

static int	term_tree_choice(char *buf, int *arr, t_line_list **first,
		t_hist_list **hist)
{
	if (arr[1] == 1)
		return (term_spec_char(buf[0], first, hist));
	//else if (arr[1] == 2)
	//	copy_cut_mode(first, buf[0]);
	//else if (arr[1] == 3)
	//	copy_paste(first);
	else if (arr[1] == 4)
		return (hist_change(buf[arr[0] - 1] - 64, hist, first));
	else if (arr[1] == 5)
		term_mv_horizontal(buf[arr[0] -1] - 64, first);
	else if (arr[1] == 6)
		term_mv_cursor(buf[arr[0] - 1], first);
	//else if (arr[1] == 7)
	//	return (yank_line(buf[0], first));
	return (buf[0]);
}

int			term_edit_line(char *buf, int len, t_line_list **first,
		t_hist_list **hist)
{
	int		i;
	int		arr[2];
	
	i = 0;
	while (g_edit_line[i].id != NULL &&
			ft_strncmp(g_edit_line[i].id, buf, len) != 0)
		i++;
	if (g_edit_line[i].ret == 0)
		return (0);
	arr[0] = len;
	arr[1] = g_edit_line[i].ret;
	return (term_tree_choice(buf, arr, first, hist));
}
