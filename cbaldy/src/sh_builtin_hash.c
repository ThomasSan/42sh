/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_hash.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 17:02:17 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/21 17:04:29 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_builtin_hash(char **com)
{
	int		i;

	i = 0;
	if (com[1] != NULL)
		while (ft_strcmp(g_hash[i], com[1]) < 0)
			i++;
	while (g_hash[i] != NULL)
	{
		ft_putendl(g_hash[i]);
		i++;
	}
	return (0);
}
