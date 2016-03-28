/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_list_ft.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 18:33:06 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/26 19:20:02 by cbaldy           ###   ########.fr       */
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
