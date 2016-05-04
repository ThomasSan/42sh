/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_list_ft2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/30 15:33:21 by dbaldy            #+#    #+#             */
/*   Updated: 2016/04/30 16:20:45 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_line_list			*str_to_line(char *str, t_line_list *first)
{
	t_line_list		*new_line;
	t_com_list		*sub_line;
	t_com_list		*tmp;

	new_line = line_list_new(0);
	new_line->previous = first;
	sub_line = NULL;
	while (*str != '\0')
	{
		tmp = (sub_line == NULL) ? NULL : sub_line;
		sub_line = com_list_new(*str);
		if (tmp == NULL)
			new_line->begin = sub_line;
		else
			tmp->next = sub_line;
		sub_line->previous = tmp;
		if (*str == '\n')
			break ;
		str++;
	}
	if (*str != '\0')
		new_line->next = str_to_line(str + 1, new_line);
	return (new_line);
}
