/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_list_ft.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 18:33:06 by cbaldy            #+#    #+#             */
/*   Updated: 2016/04/28 13:01:41 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_parse	*parse_list_new(char **arg, int type)
{
	t_parse	*new;

	if ((new = (t_parse *)malloc(sizeof(t_parse))) == NULL)
		return (NULL);
	new->next = NULL;
	new->arg = arg;
	new->type = type;
	return (new);
}

int		parse_list_pushback(t_parse *new, t_parse **head)
{
	t_parse *tmp;

	tmp = *head;
	if (tmp == NULL)
		*head = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (0);
}

int		parse_list_free(t_parse *head)
{
	t_parse	*tmp;

	while (head != NULL)
	{
		tmp = head->next;
		if (head->arg != NULL)
			ft_free_tab(head->arg);
		free(head);
		head = tmp;
	}
	return (0);
}
