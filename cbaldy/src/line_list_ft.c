/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_list_ft.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 17:26:00 by cbaldy            #+#    #+#             */
/*   Updated: 2016/04/27 19:16:14 by dbaldy           ###   ########.fr       */
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

t_line_list	*line_list_dup(t_line_list *var)
{
	t_line_list	*tmp;

	if (var == NULL)
		return (NULL);
	if ((tmp = (t_line_list*)malloc(sizeof(t_line_list))) == NULL)
		return (NULL);
	tmp->begin = com_list_dup(var->begin);
	tmp->next = NULL;
	tmp->previous = NULL;
	tmp->marge = var->marge;
	if (var->next == NULL)
		return (tmp);
	else
	{
		tmp->next = line_list_dup(var->next);
		tmp->next->previous = tmp;
	}
	return (tmp);
}

int			line_list_free(t_line_list *first)
{
	t_line_list	*tmp;

	if (first == NULL)
		return (0);
	while (first->previous)
		first = first->previous;
	tmp = first->next;
	com_list_free(first->begin);
	first->next = NULL;
	first->previous = NULL;
	free(first);
	if (tmp != NULL)
	{
		tmp->previous = NULL;
		line_list_free(tmp);
	}
	return (0);
}

int			line_list_get_marge(t_line_list *first)
{
	while (first != NULL)
	{
		if (first->marge > 0)
			return (first->marge);
		first = first->previous;
	}
	return (0);
}
