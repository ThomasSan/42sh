/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_change.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/23 14:54:11 by cbaldy            #+#    #+#             */
/*   Updated: 2016/04/23 15:00:41 by cbaldy           ###   ########.fr       */
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
		ft_dprintf(STDIN_FILENO, "%c", s[i]);
		i++;
	}
	ft_tputs("ce", 1, 0);
	return (0);
}


static int	move_hist(int move, t_hist_list **hist, t_line_list **first)
{
	t_hist_list		*buf;

	if ((*first)->marge != 0 && (*first)->previous != NULL)
		return (-1);
	else if (move == 1 && (*hist)->next != NULL)
		buf = (*hist)->next;
	else if (move == 2 && (*hist)->previous != NULL)
		buf = (*hist)->previous;
	else
		return (-1);
	while (term_mv_horizontal(4, first, 0) != -1)
		;
	line_list_free((*hist)->old);
	(*hist)->old = line_list_dup(*first);
	line_list_free(*first);
	(*hist) = buf;
	return (0);
}

int			hist_change(int move, t_hist_list **hist, t_line_list **first)
{
	char		*str;
	int			save;

	save = line_list_get_marge(*first);
	if (move_hist(move, hist, first) == -1)
		return (0);
	ft_tputs("cd", 1, 0);
	*first = line_list_dup((*hist)->old);
	str = line_list_retrieve(*first);
	hist_print_line(str);
	(*first)->marge = save;
	while ((*first)->next != NULL)
		*first = (*first)->next;
	g_local->curs = (*first)->marge + 1 + com_list_count((*first)->begin);
	free(str);
	return (0);
}
