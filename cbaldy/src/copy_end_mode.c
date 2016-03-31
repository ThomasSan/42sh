/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_end_mode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 14:42:54 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/31 15:01:15 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	copy_reset_line(t_line_list *first)
{
	int			save;
	int			j;
	int			len_list;

	save = g_local->curs;
	len_list = com_list_count(first->begin);
	ft_tputs("ce", 1, 0);
	while (term_mv_horizontal(4, &first) == 0)
		ft_tputs("dc", 1, 0);
	print_command(first->begin, 0, first);
	while (term_mv_horizontal(4, &first) == 0)
		;
	j = first->marge;
	while (j++ != save - 1)
		term_mv_horizontal(3, &first);
	return (0);
}

int			copy_paste(t_line_list **first)
{
	t_com_list	*new;
	int			i;

	if ((new = com_list_reconstruct(g_paste)) == NULL)
		return (0);
	com_list_add(&((*first)->begin), new, (*first)->marge);
	copy_reset_line(*first);
	i = com_list_count((*first)->begin);
	while (term_mv_horizontal(3, first) == 0)
		;
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

int			copy_end_mode(t_line_list **first)
{
	char		*str;
	t_com_list	*tmp;
	int			i;

	str = ft_strnew(com_list_count((*first)->begin) + 1);
	tmp = (*first)->begin;
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
	copy_clean_com(&((*first)->begin));
	if (g_paste != NULL && str[0] != '\0')
		free(g_paste);
	if (str[0] != '\0')
		g_paste = ft_strdup(str);
	free(str);
	return (copy_reset_line(*first));
}
