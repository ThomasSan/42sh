/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_list_ft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/25 17:23:22 by cbaldy            #+#    #+#             */
/*   Updated: 2016/04/30 15:58:59 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_com_list	*com_list_new(char value)
{
	t_com_list	*tmp;

	if ((tmp = (t_com_list *)malloc(sizeof(t_com_list))) == NULL)
		return (NULL);
	tmp->c = value;
	tmp->op = 0;
	tmp->next = NULL;
	tmp->previous = NULL;
	return (tmp);
}

int			com_list_count(t_com_list *begin)
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

char		*com_list_retrieve(t_com_list *begin)
{
	char		*str;
	int			i;

	str = ft_strnew(com_list_count(begin) + 1);
	i = 0;
	while (begin != NULL)
	{
		str[i] = begin->c;
		i++;
		begin = begin->next;
	}
	return (str);
}

int			com_list_free(t_com_list *begin)
{
	t_com_list	*tmp;

	if (begin == NULL)
		return (0);
	tmp = begin->next;
	free(begin);
	while (tmp != NULL)
	{
		begin = tmp;
		tmp = begin->next;
		free(begin);
	}
	return (0);
}

t_com_list	*com_list_dup(t_com_list *begin)
{
	t_com_list	*tmp[2];

	tmp[1] = NULL;
	while (begin != NULL)
	{
		tmp[0] = com_list_new(begin->c);
		if (tmp[1] != NULL)
			tmp[1]->next = tmp[0];
		tmp[0]->previous = tmp[1];
		tmp[1] = tmp[0];
		begin = begin->next;
	}
	while (tmp[1] != NULL && tmp[1]->previous != NULL)
		tmp[1] = tmp[1]->previous;
	return (tmp[1]);
}
