/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_list_ft.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 17:26:00 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/31 12:27:57 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_line_list	*line_list_new(int marge)
{
	t_line_list	*new;

	if ((new = (t_line_list *)malloc(sizeof(t_line_list))) == NULL)
		return (NULL);
	new->next = NULL;
	new->previous = NULL;
	new->begin = NULL;
	new->marge = marge;
	return (new);
}

char		*line_list_retrieve(t_line_list *first)
{
	char	*str;
	char	*tmp;

	str = com_list_retrieve(first->begin);
	first = first->next;
	while (first != NULL)
	{
		tmp = com_list_retrieve(first->begin);
		str = mod_strjoin(str, tmp, 3);
		first = first->next;
	}
	return (str);
}
/*
int			line_list_free(t_line_list *first)
{
	t_line_list	*tmp;

	while (first != NULL)
	{
		tmp = first->next;
		com_list_free(first->begin);
		free(first);
		first = tmp;
	}
	return (0);
}*/
