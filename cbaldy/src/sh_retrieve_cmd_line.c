/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_retrieve_cmd_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 17:28:38 by cbaldy            #+#    #+#             */
/*   Updated: 2016/04/29 14:07:17 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*sh_reset_cmd_line(t_line_list **first, t_hist_list **hist)
{
	t_hist_list	*tmp;

	line_list_free(*first);
	tmp = (*hist)->next;
	free(*hist);
	*hist = tmp;
	ft_putchar_fd('\n', STDIN_FILENO);
	return (NULL);
}

char		*sh_retrieve_cmd_line(t_line_list *first, int end,
		t_hist_list **hist)
{
	char	*cmd;

	clear_curr_compl();
	ft_tputs("cd", 1, 0);
	if (end == 3)
		return (sh_reset_cmd_line(&first, hist));
	while (first->previous != NULL)
		first = first->previous;
	cmd = line_list_retrieve(first);
	if (end == 4)
	{
		if (cmd[0] == '\0')
			exit(sh_reset_term());
		else if (mini_finish_line(cmd) < 0)
		{
			free(cmd);
			return (sh_reset_cmd_line(&first, hist));
		}
	}
	return (cmd);
}
