/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_list_ft2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 17:18:32 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/23 12:18:57 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_com_list	*com_list_reconstruct(char *s)
{
	int			i;
	t_com_list	*new;
	t_com_list	*tmp;

	if (s == NULL)
		return (0);
	i = 0;
	tmp = NULL;
	while (s[i] != 0)
	{
		if ((new = com_list_new(s[i])) == NULL)
			return (NULL);
		if (tmp != NULL)
		{
			tmp->next = new;
			new->previous = tmp;
		}
		tmp = new;
		i++;
	}
	while (tmp->previous != NULL)
		tmp = tmp->previous;
	return (tmp);
}

int			com_list_remove(t_com_list *del, t_com_list **begin)
{
	t_com_list	*tmp[2];

	tmp[0] = del->previous;
	tmp[1] = del->next;
	free(del);
	del = NULL;
	if (tmp[0] != NULL)
		tmp[0]->next = tmp[1];
	else
		*begin = tmp[1];
	if (tmp[1] != NULL)
		tmp[1]->previous = tmp[0];
	return (0);
}

static int	com_list_insert(t_com_list **begin, t_com_list *new)
{
	t_com_list	*tmp[2];
	int			i;

	i = g_local->prompt;
	tmp[0] = *begin;
	while (tmp[0]->next != NULL && i < g_local->curs - 2)
	{
		tmp[0] = tmp[0]->next;
		i++;
	}
	tmp[1] = tmp[0]->next;
	tmp[0]->next = new;
	new->previous = tmp[0];
	while (new->next != NULL)
		new = new->next;
	if (tmp[1] != NULL)
	{
		new->next = tmp[1];
		tmp[1]->previous = new;
	}
	return (0);
}

int			com_list_add(t_com_list **begin, t_com_list *new)
{
	t_com_list	*tmp;

	if (new == NULL)
		return (0);
	if (*begin == NULL)
		*begin = new;
	else if (g_local->curs - g_local->prompt == 1)
	{
		tmp = *begin;
		*begin = new;
		while (new->next != NULL)
			new = new->next;
		new->next = tmp;
		tmp->previous = new;
	}
	else
		com_list_insert(begin, new);
	return (0);
}

char		*com_list_join(t_com_list *begin)
{
	char	*str[3];

	str[0] = "";
	str[1] = "";
	if (g_local->begin != NULL)
		str[0] = com_list_retrieve(g_local->begin);
	if (begin != NULL)
		str[1] = com_list_retrieve(begin);
	str[2] = ft_strjoin(str[0], str[1]);
	if (str[0][0] != '\0')
		free(str[0]);
	if (str[1][0] != '\0')
		free(str[1]);
	return (str[2]);
}
