/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 10:56:33 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/29 14:55:10 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** 0 init menu | 1 test if menu already opened | 2 clear menu
*/

t_line		*menu_history(int flag)
{
	static t_line	*line;

	if (flag == 0 && line == NULL)
	{
		init_debut(&line);
		return (line);
	}
	else if (flag == 0)
		return (line);
	else if (flag == 1 && line == NULL)
		return (NULL);
	else if (flag == 1)
		return (line);
	else if (flag == 2 && line != NULL)
		clear_tline(&line);
	return (NULL);
}

/*
** reprint line in case of match
*/


static int	print_change(t_com_list **begin, t_hist_list **hist, t_line *line,
		int flag)
{
	char	*str;

	if (flag == 1)
	{	
		while (term_mv_horizontal(4, 0) != -1)
			;
		ft_tputs("cd", 1, 0);
		*begin = com_list_dup((*hist)->old);
		str = com_list_retrieve(*begin);
		hist_print_line(str);
		g_local->curs = g_local->prompt + 1 + (int)ft_strlen(str);
		free(str);
	}
	update_search_bar(line);
		
}

/*
** CTRL+R open search menu backwards
*/

int			search_history(t_com_list **begin, t_hist_list **hist)
{
	char			*str;
char			*tmp;
	t_hist_list		*buf;
	t_line			*line;

	line = menu_history(0);
	if ((str = line_of_command(line) && ;
	buf = *hist;
	while (*hist)
	{
		tmp = com_list_retrieve(*hist->begin);
		if (ft_strstr(tmp, str) != NULL)
			break ;
		*hist = (*hist)->next;
	}
	if (*hist == NULL)
	{
		*hist = buf;
		print_change(begin, hist, str, 0);
	}
	else
		print_change(begin, hist, str, 1);
	free(str);
	free(tmp);
	return (0);
}
