/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_retrieve_cmd_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 17:28:38 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/30 10:35:22 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*sh_reset_cmd_line(t_com_list **begin, t_hist_list **hist)
{
	t_hist_list	*tmp;

	com_list_free(*begin);
	com_list_free(g_local->begin);
	tmp = (*hist)->next;
	free(*hist);
	*hist = tmp;
	return (NULL);
}

char	*sh_retrieve_cmd_line(t_com_list **begin, int end, t_hist_list **hist)
{
	t_com_list	*tmp;
	char		*str;
	//char		*dump;

	clear_curr_compl();
	if (end == 3)
		return (sh_reset_cmd_line(begin, hist));
	if (g_local->begin != NULL)
	{
		tmp = g_local->begin;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = *begin;
		(*begin)->previous = tmp;
		*begin = g_local->begin;
		com_list_free(g_local->begin);
	}
	str = com_list_retrieve(*begin);
	if (end == 4 && str[0] == '\0')
		exit(sh_reset_term());
	//dump = ft_strtrim(str);
	//free(str);
	return (str);
}
