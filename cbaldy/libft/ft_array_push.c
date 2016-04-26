/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_push.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 10:18:47 by dbaldy            #+#    #+#             */
/*   Updated: 2016/04/26 14:00:52 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static int		add_push(char ***table, char *to_push)
{
	if ((*table = (char**)malloc(sizeof(char*) * 2)) == NULL)
		return (-1);
	(*table)[0] = ft_strdup(to_push);
	(*table)[1] = NULL;
	return (0);
}


int				ft_array_push(char ***table, char *to_push)
{
	int		size;
	char	**res;

	size = 0;
	if (*table == NULL)
		return (add_push(table, to_push));
	while ((*table)[size])
		size++;
	if ((res = (char**)malloc(sizeof(char*) * (size + 2))) == NULL)
		return (-1);
	res[0] = ft_strdup(to_push);
	size = 0;
	while ((*table)[size])
	{
		res[size + 1] = ft_strdup((*table)[size]);
		size++;
	}
	res[size + 1] = NULL;
	ft_freetab((*table));
	(*table) = res;
	return (0);
}
