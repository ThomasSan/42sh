/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_complete_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 16:49:46 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/23 12:43:22 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	increase_line(t_com_list *begin, char *test, char *word)
{
	int			i;
	t_com_list	*buf;

	buf = begin;
	i = g_local->prompt;
	while (i++ < g_local->curs)
		buf = buf->next;
	while (buf->next && buf->next->c != ' ')
	{
		buf = buf->next;
		g_local->curs++;
	}
	while (*word)
	{
//		ed_add_char(&begin, *word);
		word++;
	}
	return (0);
	test = NULL;
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

	test = NULL;
	while ((debut->var)[size_curr_word])
	{
		test = ft_strsub(debut->var, 0, size_curr_word);
		if (can_increase(debut, test, size_curr_word) != 0)
			return (size_curr_word - 1);
		if (test != NULL)
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
	if (size_curr_word == (int)ft_strlen(debut->var))
		return (0);
	size_curr_word = get_compl_max(debut, size_curr_word);
//	ft_dprintf(1, "%d %d %d\n", (int)ft_strlen(word), size_curr_word, debut->next->nb);
	if (size_curr_word == (int)(ft_strlen(word)))
	{
		if (debut->next->nb != 0 && g_curr_compl == NULL)
			return (1);
		else if (debut->next->nb != 0)
			while (debut->prev->select != 1)
				debut = debut->next;
		debut->prev->select = 0;
		debut->select = 1;
		test = ft_strdup(debut->var);
	}
	else
		test = ft_strsub(debut->var, 0, size_curr_word);
//	ft_dprintf(1, "%s\n", test);
//	exit(1);
	return (increase_line(begin, test, word));
}
