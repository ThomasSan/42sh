/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_hist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 11:57:11 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/30 12:34:27 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			*hist_list_new(t_hist_list **hist)
{
	t_hist_list	*new;

	if ((new = (t_hist_list *)malloc(sizeof(t_hist_list))) == NULL)
		return (NULL);
	new->old = NULL;
	new->next = (*hist != NULL) ? (*hist) : NULL;
	new->previous = NULL;
	new->nb = (*hist != NULL) ? (*hist)->nb + 1 : 1;
	if ((*hist) != NULL)
		(*hist)->previous = new;
	*hist = new;
	return (0);
}

int			hist_print_line(char *s)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			ft_dprintf(STDIN_FILENO, " ");
		else
			ft_dprintf(STDIN_FILENO, "%c", s[i]);
		i++;
	}
	ft_tputs("cd", 1, 0);
	return (0);
}


static int	move_hist(int move, t_hist_list **hist, t_com_list **begin)
{
	t_hist_list		*buf;

	if (move == 1 && (*hist)->next != NULL)
		buf = (*hist)->next;
	else if (move == 2 && (*hist)->previous != NULL)
		buf = (*hist)->previous;
	else
		return (-1);
	com_list_free((*hist)->old);
	(*hist)->old = com_list_dup(*begin);
	com_list_free(*begin);
	(*hist) = buf;
	return (0);
}

int			hist_change(int move, t_hist_list **hist, t_com_list **begin)
{
	char	*str;
	
	if (move_hist(move, hist, begin) == -1)
		return (0);
	while (term_mv_horizontal(4, 0) != -1)
		;
	ft_tputs("cd", 1, 0);
	*begin = com_list_dup((*hist)->old);
	str = com_list_retrieve(*begin);
	hist_print_line(str);
	g_local->curs = g_local->prompt + 1 + (int)ft_strlen(str);
	free(str);
	return (0);
}
