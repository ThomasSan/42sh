/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_get_path2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 19:08:59 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/28 19:26:49 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*cd_get_path2(char *com)
{
	char	*path;

	if (com[0] == '/')
		return (ft_strdup(com));
	else if ((path = getcwd(NULL, 0)) == NULL)
		return (NULL);
	path = mod_strjoin(mod_strjoin(path, "/", 1), com, 1);
	return (path);
}
