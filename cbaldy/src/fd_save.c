/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_save.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 15:02:36 by cbaldy            #+#    #+#             */
/*   Updated: 2016/04/29 10:09:38 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		*fd_save(void)
{
	int		*save;

	if ((save = (int *)malloc(sizeof(int) * 3)) == NULL)
		return (NULL);
	save[0] = dup(STDIN_FILENO);
	save[1] = dup(STDOUT_FILENO);
	save[2] = dup(STDERR_FILENO);
	return (save);
}

int		fd_reset(int *save)
{
	dup2(save[0], STDIN_FILENO);
	dup2(save[1], STDOUT_FILENO);
	dup2(save[2], STDERR_FILENO);
	close(save[0]);
	close(save[1]);
	close(save[2]);
	return (0);
}
