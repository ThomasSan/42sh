/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 19:08:28 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/15 19:41:20 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			sh_minishell(void)
{
	int		end;
	char	*str;

	ft_dprintf(STDIN_FILENO, "$>");
	signal(SIGINT, SIG_IGN);
	str = NULL;
	end = get_next_line(STDIN_FILENO, &str);
	if (str != NULL && ft_strlen(str) != 0)
		sh_exec_list(str);
	else if (str == NULL)
		exit(1);
	if (str != NULL)
	{
		free(str);
		str = NULL;
	}
	return (0);
}
