/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_edit_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/23 16:44:46 by cbaldy            #+#    #+#             */
/*   Updated: 2016/04/29 10:19:22 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_edit_line	g_here_edit_line[] = {
	{"\x1c", 1},
	{"\x3", 1},
	{"\x4", 1},
	{"\x12", 1},
	{"\x15", 7},
	{"\x0b", 7},
	{"\x19", 7},
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

static int	heredoc_spec_char(char buf)
{
	if (buf == 28)
	{
		ft_free_tab(g_env);
		sh_reset_term();
		ft_dprintf(STDOUT_FILENO, "\t21sh: exit\n");
		exit(0);
	}
	return (buf);
}

static int	heredoc_tree_choice(char *buf, int *arr, t_line_list **first)
{
	if (arr[1] == 1)
		return (heredoc_spec_char(buf[0]));
	else if (arr[1] == 5)
		term_mv_horizontal(buf[arr[0] - 1] - 64, first, 0);
	else if (arr[1] == 6)
		term_mv_cursor(buf[arr[0] - 1], first);
	else if (arr[1] == 7)
		return (yank_line(buf[0], first));
	return (buf[0]);
}

int			heredoc_edit_line(char *buf, int len, t_line_list **first)
{
	int		i;
	int		arr[2];

	i = 0;
	while (g_here_edit_line[i].id != NULL &&
			ft_strncmp(g_here_edit_line[i].id, buf, len) != 0)
		i++;
	if (g_here_edit_line[i].ret == 0)
		return (0);
	arr[0] = len;
	arr[1] = g_here_edit_line[i].ret;
	return (heredoc_tree_choice(buf, arr, first));
}
