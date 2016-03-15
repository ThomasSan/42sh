/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_end_mode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 14:42:54 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/07 15:57:01 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	copy_reset_line(t_com_list *begin)
{
	int			save;
	int			j;
	int			len_list;

	save = g_local->curs;
	len_list = com_list_count(begin);
	ft_tputs("dc", 1, 0);
	while (term_mv_horizontal(4, 0) == 0)
		ft_tputs("dc", 1, 0);
	ft_tputs("cd", 1, 0);
	print_command(begin, 0);
	while (term_mv_horizontal(4, 0) == 0)
		;
	j = g_local->prompt;
	while (j++ != save - 1)
		term_mv_horizontal(3, len_list);
	return (0);
}

int			copy_paste(t_com_list **begin)
{
	t_com_list	*new;

	if ((new = com_list_reconstruct(g_paste)) == NULL)
		return (0);
	com_list_add(begin, new);
	copy_reset_line(*begin);
	return (0);
}

int static	copy_clean_com(t_com_list **begin)
{
	t_com_list	*tmp[2];

	tmp[0] = *begin;
	while (tmp[0] != NULL)
	{
		if (tmp[0]->op == 1)
		{
			tmp[0]->op = 0;
			tmp[0] = tmp[0]->next;
		}
		else if (tmp[0]->op == 2)
		{
			tmp[1] = tmp[0]->next;
			com_list_remove(tmp[0], begin);
			tmp[0] = tmp[1];
		}
		else
			tmp[0] = tmp[0]->next;
	}
	return (0);
}

int			copy_end_mode(t_com_list **begin)
{
	char		*str;
	t_com_list	*tmp;
	int			i;

	str = ft_strnew(com_list_count(*begin) + 1);
	tmp = *begin;
	i = 0;
	while (tmp != NULL)
	{
		if (tmp->op != 0)
		{
			str[i] = tmp->c;
			i++;
		}
		tmp = tmp->next;
	}
	copy_clean_com(begin);
	if (g_paste != NULL)
		free(g_paste);
	g_paste = ft_strdup(str);
	free(str);
	copy_reset_line(*begin);
	return (0);
}
