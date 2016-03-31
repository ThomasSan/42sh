/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_retrieve_cmd_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 17:28:38 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/30 19:19:22 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*static char	*sh_reset_cmd_line(t_com_list **begin, t_hist_list **hist)
{
	t_hist_list	*tmp;

	com_list_free(*begin);
	tmp = (*hist)->next;
	free(*hist);
	*hist = tmp;
	return (NULL);
}*/

char	*sh_retrieve_cmd_line(t_line_list *first, int end, t_hist_list **hist)
{
	char	*cmd;

	//clear_curr_compl();
	//if (end == 3)
	//	return (sh_reset_cmd_line(begin, hist));
	while (first->previous != NULL)
		first = first->previous;
	cmd = line_list_retrieve(first);
	if (end == 4 && cmd[0] == '\0')
		exit(sh_reset_term());
	return (cmd);
	*hist = NULL;
}
