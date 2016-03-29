/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_read_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 15:36:22 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/29 19:22:52 by dbaldy           ###   ########.fr       */
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
	g_local->prompt = i;
	g_local->curs = i + 1;
	g_local->begin = NULL;
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &w) < 0)
		return (0);
	g_local->nb_col = w.ws_col;
	sh_set_term();
	ft_tputs("cd", 1, 0);
	return (0);
}

static int	sh_read_prompt(t_com_list **begin, t_hist_list **hist)
{
	int			len;
	char		buf[10];
	int			i;

	i = 0;
	len = read(STDIN_FILENO, buf, 10);
	ft_bzero(&buf[len], 10 - len);
	if (ft_strcmp(buf, "\x09") != 0)
		clear_curr_compl();
	if  (manage_search_hist(buf, begin, hist, 1) != 0 &&
			buf[0] <= 32 && buf[1] == 0)
		exit_search_hist(begin);
	if (manage_search_hist(buf, begin, hist, 1) != 0 && buf[0] > 32 &&
			buf[0] <= 127 && buf[1] == 0)
		i = manage_search_hist(buf, begin, hist, 0);
	else if ((len != 1 || buf[0] < 31 || buf[0] > 127) &&
			(len != 1 || buf[0] != 10))
		i = term_edit_line(buf, len, begin, hist);
	else if (len == 1)
		i = term_write_line(begin, buf[0]);
	return (i);
}

int			sh_prompt(void)
{
	t_com_list			*begin;
	char				*str;
	int					i;
	t_hist_list			*modif_hist;

	sh_print_prompt();
	i = 0;
	begin = NULL;
	modif_hist = retrieve_history(0, NULL);
	while (i != 10 && i != 4 && i != -1 && i != 3)
		i = sh_read_prompt(&begin, &modif_hist);
	if ((str = sh_retrieve_cmd_line(&begin, i, &modif_hist)) == NULL)
		return (0);
	sh_reset_term();
	signal(SIGINT, SIG_IGN);
	sh_exec_control(str);
	retrieve_history(1, begin);
	clear_hist(&modif_hist);
	free(str);
	return (0);
}
