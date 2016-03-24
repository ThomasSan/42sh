/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_1_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 16:17:20 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/24 15:48:27 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_free_tab(char **arr)
{
	int		i;

	if (arr != NULL)
	{
		i = 0;
		while (arr[i] != NULL)
		{
			free(arr[i]);
			arr[i] = NULL;
			i++;
		}
		free(arr);
		arr = NULL;
		return (0);
	}
	return (0);
}

char	*mod_strjoin(char *s1, char *s2, int fr)
{
	char	*tmp;

	if (s1 == NULL)
		tmp = ft_strdup(s2);
	else if (s2 == NULL)
		tmp = ft_strdup(s1);
	else
		tmp = ft_strjoin(s1, s2);
	if (fr == 1)
		free(s1);
	else if (fr == 2)
		free(s2);
	return (tmp);
}

char	*mod_strsub(char *s, unsigned int start, size_t len, int fr)
{
	char	*tmp;

	tmp = ft_strsub(s, start, len);
	if (fr == 1)
		free(s);
	return (tmp);
}
