/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_retrieve_cmd_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 17:28:38 by cbaldy            #+#    #+#             */
/*   Updated: 2016/04/29 17:50:03 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*sh_retrieve_cmd_line(t_line_list *first, int end)
{
	char	*cmd;

	clear_curr_compl();
	ft_tputs("cd", 1, 0);
	if (end == 3)
	{
		ft_putchar_fd('\n', STDIN_FILENO);
		return (NULL);
	}
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
			return (NULL);
		}
	}
	return (cmd);
}
