/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 10:56:33 by dbaldy            #+#    #+#             */
/*   Updated: 2016/04/23 15:06:08 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		line_of_command(t_line *debut, char **str)
{
	t_line	*buf;
	int		size;
	char	*ret;
	int		i;

	i = 0;
	size = 0;
	buf = debut;
	while (buf->next)
	{
		buf = buf->next;
		size++;
	}
	if ((ret = (char*)malloc(sizeof(char) * (size + 1))) == NULL)
		return (-1);
	buf = debut;
	while (buf->next)
	{
		ret[i] = buf->c;
		i++;
		buf = buf->next;
	}
	ret[i] = '\0';
	*str = ret;
	return (0);
}

static int		change_line(t_line_list **first, t_hist_list **hist)
{
	char	*str;
	int		save;

	save = line_list_get_marge(*first);
	while (term_mv_horizontal(4, first, 0) != -1)
		;
	ft_notputs("cd", 1);
	save = line_list_get_marge(*first);
	line_list_free(*first);
	*first = line_list_dup((*hist)->old);
	str = line_list_retrieve(*first);
	hist_print_line(str);
	(*first)->marge = save;
	while ((*first)->next != NULL)
		*first = (*first)->next;
	g_local->curs = (*first)->marge + 1 + com_list_count((*first)->begin);
	free(str);
	return (0);
}

static int		hist_boucle(t_hist_list **hist, char *str)
{
	char		*tmp;

	while (*hist)
	{
		tmp = line_list_retrieve((*hist)->old);
		if (ft_strstr(tmp, str) != NULL)
		{
			free(tmp);
			return (1);
		}
		free(tmp);
		*hist = (*hist)->next;
	}
	return (0);
}

int			exit_search_hist(t_line_list **first)
{
	exit_completion(*first);
	manage_search_hist(NULL, NULL, NULL, 2);
	return (0);
}

/*
** check if search bar matches with history
*/

int			search_bar_history(t_line_list **first, t_hist_list **hist,
		t_line *line, int flag)
{
	char					*str;
	static t_hist_list		*buf;
	int						ret;

	if (flag == 1)
	{
		buf = NULL;
		return (0);
	}
	line_of_command(line, &str);
	prepare_search_bar(first, hist);
	if (buf == NULL)
		buf = *hist;
	else
		*hist = buf;
	if ((ret = hist_boucle(hist, str)) == 0)
		*hist = buf;
	change_line(first, hist);
	free(str);
	return (ret);
}
