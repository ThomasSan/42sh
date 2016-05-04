/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_hash.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 17:02:17 by cbaldy            #+#    #+#             */
/*   Updated: 2016/05/03 15:56:54 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_builtin_hash(char **com)
{
	int		i;
	char	**hash;

	i = 0;
	if ((hash = hash_get_tab()) == NULL)
	{
		ft_dprintf(STDERR_FILENO, "shell: hash: no file found\n");
		return (1);
	}
	while (hash != NULL && hash[i] != NULL)
	{
		ft_putendl(hash[i]);
		i++;
	}
	ft_free_tab(hash);
	return (0);
	*com = NULL;
}
