/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list_ft.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 16:17:54 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/09 19:46:53 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_exec_list		*exec_list_new(char *str, int connect)
{
	t_exec_list	*tmp;

	if ((tmp = (t_exec_list *)malloc(sizeof(t_exec_list))) == NULL)
		return (NULL);
	tmp->arg = ft_strsplit(str, ' ');
	tmp->clog = connect;
	tmp->next = NULL;
	tmp->previous = NULL;
	return (tmp);
}

int			exec_list_add(t_exec_list **begin, t_exec_list *new)
{
	t_exec_list	*tmp;

	if (new == NULL)
		return (0);
	if (*begin == NULL)
		*begin = new;
	else
	{
		tmp = *begin;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
		new->previous = tmp;
	}
	return (0);
}

int		exec_list_count(t_exec_list *begin)
{
	int		i;

	i = 0;
	while (begin != NULL)
	{
		i++;
		begin = begin->next;
	}
	return (i);
}
