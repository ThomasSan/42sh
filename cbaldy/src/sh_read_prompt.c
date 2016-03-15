/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_read_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 15:36:22 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/09 10:48:45 by cbaldy           ###   ########.fr       */
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
	i += ft_dprintf(STDIN_FILENO, "$>");
	g_local->prompt = i;
	g_local->curs = i + 1;
	g_local->begin = NULL;
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &w) < 0)
		return (0);
	g_local->nb_col = w.ws_col;
	return (0);
}

static char	*sh_get_line(t_com_list **begin)
{
	t_com_list	*tmp;
	
	if (g_local->begin == NULL)
		return (com_list_retrieve(*begin));
	tmp = g_local->begin;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = *begin;
	(*begin)->previous = tmp;
	*begin = g_local->begin;
	return (com_list_retrieve(*begin));
}

static int	sh_read_prompt(t_com_list **begin, t_hist_list **hist)
{
	int			len;
	char		*buf;
	int			i;

	buf = ft_strnew(10);
	i = 0;
	len = read(STDIN_FILENO, buf, 9);
	if ((len != 1 || buf[0] < 31 || buf[0] > 127) &&
			(len != 1 || buf[0] != 10))
		i = term_edit_line(buf, len, begin, hist);
	else if (len == 1)
		i = term_write_line(begin, buf[0]);
	free(buf);
	return (i);
}

int			sh_prompt(void)
{
	t_com_list			*begin;
	static t_hist_list	*hist;
	char				*str;
	int					i;

	sh_print_prompt();
	i = 0;
	begin = NULL;
	hist_list_new(&hist);
	while (i != 10 && i != 4 && i != -1 && i != 3)
		i = sh_read_prompt(&begin, &hist);
	if (i == 3)
		return (0);
	str = sh_get_line(&begin);
	if (i == 4 && str[0] == '\0')
		exit(sh_reset_term());
	ft_printf("%s\n", str);
	hist_add_elem(begin, &hist);
	if (str != NULL && ft_strlen(str) != 0)
		sh_split_com(str);
	if (str != NULL)
		free(str);
	return (0);
}
