/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_read_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 15:36:22 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/24 16:54:17 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_print_prompt(void)
{
	int				i;
	struct winsize	w;

	i = 0;
	if ((i = sh_is_new_var("USER")) != -1)
		i = ft_dprintf(STDIN_FILENO, &(ft_strchr(g_env[i], '=')[1]));
	if (i < 0)
		i = 0;
	i += ft_dprintf(STDIN_FILENO, "$> ");
	g_local->prompt = i;
	g_local->curs = i + 1;
	g_local->begin = NULL;
	g_local->completion = 0;
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &w) < 0)
		return (0);
	g_local->nb_col = w.ws_col;
	sh_set_term();
	ft_tputs("cd", 1, 0);
	return (0);
}

static char	*sh_get_line(t_com_list **begin, int end)
{
	t_com_list	*tmp;
	char		*str;
	
	if (end == 3)
		return (NULL);
	if (g_local->begin != NULL)
	{
		tmp = g_local->begin;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = *begin;
		(*begin)->previous = tmp;
		*begin = g_local->begin;
	}
	str = com_list_retrieve(*begin);
	if (end == 4 && str[0] == '\0')
		exit(sh_reset_term());
	return (str);
}

static int	sh_read_prompt(t_com_list **begin, t_hist_list **hist)
{
	int			len;
	char		buf[10];
	int			i;

	i = 0;
	len = read(STDIN_FILENO, buf, 9);
	if ((len != 1 || buf[0] < 31 || buf[0] > 127) &&
			(len != 1 || buf[0] != 10))
		i = term_edit_line(buf, len, begin, hist);
	else if (len == 1)
		i = term_write_line(begin, buf[0]);
	return (i);
}

int			sh_prompt(void)
{
	t_com_list			*begin;
	static t_hist_list	*hist;
	char				*str;
	int					i;
	t_hist_list			*modif_hist;

	sh_print_prompt();
	i = 0;
	begin = NULL;
	hist_list_new(&hist);
	modif_hist = copy_hist(hist);
	while (i != 10 && i != 4 && i != -1 && i != 3)
		i = sh_read_prompt(&begin, &modif_hist);
	if ((str = sh_get_line(&begin, i)) == NULL)
		return (0);
	exit_completion(begin);
	hist_add_elem(begin, &hist);
	clear_hist(&modif_hist);
	sh_reset_term();
	signal(SIGINT, SIG_IGN);
	sh_exec_tree(str);
	free(str);
	return (0);
}
