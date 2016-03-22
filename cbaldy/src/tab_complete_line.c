/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_complete_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 16:49:46 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/22 19:46:56 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		increase_line_size(t_param *debut, t_com_list *begin, char *word)
{
	int			i;
	t_com_list	*buf;

	while (
}

int		tab_complete_line(t_param *debut, t_com_list *begin, char *word)
{
	t_param		*buf;
	char		*test;
	size_t		size_curr_word;
	int			size_min;

	buf = debut;
	test = NULL;
	while (size_curr_word < size_min)
	{
		if (test != NULL)
			free(test);
		test = ft_strsub(debut->var, 0, size_curr_word);
		while (42)
		{
			if (ft_strncmp(buf->var, test, size_curr_word) != 0)
				break ;
			buf = buf->next;
			if (buf->nb == 0)
				break ;
		}
		if (buf->nb != 0)
			break ;
		size_curr_word++;
	}
	return (increase_line_size(debut, begin, test));
}
