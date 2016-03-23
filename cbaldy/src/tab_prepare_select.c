/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_prepare_select.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 15:38:55 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/23 17:26:54 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	delete_word_compl(char *prev_var, t_com_list *begin)
{
	int		gap;

	gap = ft_strlen(prev_var) - ft_strlen(g_curr_compl->var) - 1;
	while (gap--)
		term_write_line(&begin, 127);
	return (0);
}

char		*tab_prepare_select(t_param *debut, t_com_list *begin)
{
	t_param		*buf;
	char		*test;

	buf = debut;
	if (buf->select == 2)
	{
		test = ft_strsub(debut->var, ft_strlen(g_curr_compl->var),
				ft_strlen(debut->var) - ft_strlen(g_curr_compl->var));
		buf->select = 0;
		buf->next->select = 1;
	}
	else
	{
		while (buf->prev->select == 0)
			buf = buf->next;
		test = ft_strsub(debut->var, ft_strlen(g_curr_compl->var),
				ft_strlen(debut->var) - ft_strlen(g_curr_compl->var));
		buf->prev->select = 0;
		buf->select = 1;
		delete_word_compl(debut->prev->var, begin);
	}
	return (test);
}
