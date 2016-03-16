/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_of_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/27 16:36:33 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/16 10:09:10 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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

static int		init_histor(t_hist **historique)
{
	if (((*historique) = (t_hist*)malloc(sizeof(t_hist))) == NULL)
		return (-1);
	(*historique)->next = NULL;
	(*historique)->prev = NULL;
	(*historique)->nb = 0;
	init_debut(&((*historique)->begin));
	return (0);
}

static int		clear_modhist(t_hist **mod)
{
	while ((*mod)->prev)
		(*mod) = (*mod)->prev;
	clear_thist(mod);
	return (0);
}

int				get_line_of_command(int fd, char **str)
{
	static t_hist		*historique;
	t_line				*current_line;
	char				buf[10];
	t_hist				*modif_hist;

	if (historique == NULL)
		init_histor(&historique);
	init_debut(&current_line);
	modif_hist = copy_hist(historique, current_line);
	while (buf[0] != '\n')
	{
		ft_bzero(buf, 10);
		read(fd, buf, 10);
		map_key(buf, &modif_hist, &current_line);
	}
	line_of_command(current_line, str);
	update_list(&historique, current_line);
	clear_modhist(&modif_hist);
	clear_tline(&current_line);
	modif_hist = historique;
	while (modif_hist && modif_hist->nb < HIST_SIZE)
		modif_hist = modif_hist->next;
	if (modif_hist != NULL)
		clear_thist(&modif_hist);
	return (0);
}
