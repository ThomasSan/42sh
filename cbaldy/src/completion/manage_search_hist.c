/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_search_hist.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 18:26:54 by dbaldy            #+#    #+#             */
/*   Updated: 2016/04/02 19:04:52 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		increase_nb(t_line *buf)
{
	while (buf)
	{
		buf->nb += 1;
		buf = buf->next;
	}
	return (0);
}

static int		init_debut(t_line **debut)
{
	if ((*debut = (t_line*)malloc(sizeof(t_line))) == NULL)
		return (-1);
	(*debut)->prev = NULL;
	(*debut)->next = NULL;
	(*debut)->c = ' ';
	(*debut)->select = 1;
	(*debut)->nb = 0;
	return (0);
}

static int		new_char_chaine(char n_c, t_line **chaine)
{
	t_line		*new;
	t_line		*buf;

	buf = *chaine;
	if ((new = (t_line*)malloc(sizeof(t_line))) == NULL)
		return (-1);
	while (buf->next && buf->select == 0)
		buf = buf->next;
	new->c = n_c;
	new->select = 0;
	new->next = buf;
	new->prev = buf->prev;
	buf->prev = new;
	new->nb = buf->nb;
	increase_nb(buf);
	if (new->prev != NULL)
		new->prev->next = new;
	*chaine = ((*chaine)->select == 1) ? new : *chaine;
	return (0);
}

static int		reprint_line(t_line *line, t_line_list *first, int match)
{
	ft_notputs("sf", 1);
	ft_notputs("cr", 1);
	ft_notputs("cd", 1);
	if (match == 1)
		ft_putstr_fd("bck-i-search: ", STDOUT_FILENO);
	else
		ft_putstr_fd("failing bck-i-search: ", STDOUT_FILENO);
	print_line(line);
	ft_notputs("cr", 1);
	go_back_to_selected_char(first);
	return (0);
}

int				manage_search_hist(char *buf, t_line_list **first,
		t_hist_list **hist, int check)
{
	static t_line		*line;

	if (line == NULL && check == 0)
		init_debut(&line);
	if (check == 1)
		return ((line == NULL) ? 0 : 1); 
	if (check == 2)
	{
		search_bar_history(NULL, NULL, NULL, 1);
		clear_tline(&line);
		return (0);
	}
	if (buf[0] > 32 && buf[0] <= 127 && buf[1] == 0)
	{
		if (buf[0] == 127)
			suppr_char_list(&line);
		else
			new_char_chaine(buf[0], &line);
	}
	if (search_bar_history(first, hist, line, 0) == 0)
		reprint_line(line, *first, 0);
	else
		reprint_line(line, *first, 1);
	return (0);
}
