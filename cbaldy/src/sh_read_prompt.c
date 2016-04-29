/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_read_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 15:36:22 by cbaldy            #+#    #+#             */
/*   Updated: 2016/04/29 17:47:36 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_print_prompt(void)
{
	int				i;
	struct winsize	w;

	i = 0;
	if ((i = sh_is_new_var("PS1")) != -1)
		i = ft_dprintf(STDIN_FILENO, &(ft_strchr(g_env[i], '=')[1]));
	else if ((i = sh_is_new_var("USER")) != -1)
		i = ft_dprintf(STDIN_FILENO, "%s$> ", &(ft_strchr(g_env[i], '=')[1]));
	else
		i = ft_dprintf(STDIN_FILENO, "$> ");
	g_local->curs = i + 1;
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &w) < 0)
		return (0);
	g_local->nb_col = (w.ws_col == 0 ? 1 : w.ws_col);
	sh_set_term();
	ft_tputs("cd", 1, 0);
	return (i);
}

static int	sh_read_prompt(t_line_list **first, t_hist_list **hist)
{
	int			len;
	char		buf[10];
	int			i;

	i = 0;
	len = read(STDIN_FILENO, buf, 10);
	ft_bzero(&buf[len], 10 - len);
	if (ft_strcmp(buf, "\x09") != 0)
		clear_curr_compl();
	if (manage_search_hist(buf, first, hist, 1) != 0 &&
		buf[0] <= 32 && buf[1] == 0)
	{
		exit_search_hist(first);
		if (buf[0] == 18)
			hist_change(1, hist, first);
	}
	if (manage_search_hist(buf, first, hist, 1) != 0 && ((buf[0] > 32 &&
			buf[0] <= 127 && buf[1] == 0)))
		i = manage_search_hist(buf, first, hist, 0);
	else if ((len != 1 || buf[0] < 31 || buf[0] > 127) &&
			(len != 1 || buf[0] != 10))
		i = term_edit_line(buf, len, first, hist);
	else if (len == 1)
		i = term_write_line(first, buf[0], hist);
	return (i);
}

int			sh_prompt(void)
{
	t_line_list			*first;
	char				*str;
	int					i;
	t_hist_list			*modif_hist;

	if ((first = line_list_new(sh_print_prompt())) == NULL)
		return (0);
	modif_hist = retrieve_history(0, NULL);
	i = 0;
	while (i != 10 && i != 4 && i != -1 && i != 3)
		i = sh_read_prompt(&first, &modif_hist);
	if ((str = sh_retrieve_cmd_line(first, i)) != NULL)
		sh_exec_control(str);
	if (str != NULL)
		retrieve_history(1, first);
	line_list_free(first);
	clear_hist(&modif_hist);
	free(str);
	return (0);
}
