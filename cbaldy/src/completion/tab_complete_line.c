/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_complete_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 16:49:46 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/25 15:17:09 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	increase_line(t_com_list *begin, char *test)
{
	t_com_list	*buf;
	int			i;
	int			len_list;

	i = g_local->prompt + 1;
	buf = begin;
	len_list = com_list_count(begin);
	while (buf && i < g_local->curs)
	{
		buf = buf->next;
		i++;
	}
	while (buf && buf->c != ' ')
	{
		term_mv_horizontal(3, len_list);
		buf = buf->next;
	}
	i = 0;
	while (test[i])
	{
		term_write_line(&begin, test[i]);
		i++;
	}
	free(test);
	return (0);
}

static int	can_increase(t_param *debut, char *test, size_t size_curr_word)
{
	t_param		*buf;

	buf = debut;
	while (42)
	{
		if (ft_strncmp(buf->var, test, size_curr_word) != 0)
			return (1);
		buf = buf->next;
		if (buf->nb == 0)
			return (0);
	}
	return (0);
}

static int	get_compl_max(t_param *debut, int size_curr_word)
{
	char		*test;

	while ((debut->var)[size_curr_word])
	{
		test = ft_strsub(debut->var, 0, size_curr_word);
		if (can_increase(debut, test, size_curr_word) != 0)
		{
			free(test);
			return (size_curr_word - 1);
		}
		free(test);
		size_curr_word++;
	}
	return (size_curr_word);
}

int			tab_complete_line(t_param *debut, t_com_list *begin, char *word)
{
	char		*test;
	int			size_curr_word;

	size_curr_word = ft_strlen(word) + 1;
	if (size_curr_word - 1 == (int)ft_strlen(debut->var) &&
			debut->next->nb == 0)
		return (0);
	size_curr_word = get_compl_max(debut, size_curr_word);
	if (size_curr_word == (int)(ft_strlen(word)))
	{
		if (debut->next->nb != 0 && g_curr_compl == NULL)
			return (1);
		else if (debut->next->nb != 0)
			test = tab_prepare_select(g_curr_compl->begin, begin);
		else
			return (0);
	}
	else
		test = ft_strsub(debut->var, ft_strlen(word),
				size_curr_word - ft_strlen(word));
	return (increase_line(begin, test));
}
