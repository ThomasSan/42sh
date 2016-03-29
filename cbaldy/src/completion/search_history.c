/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 10:56:33 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/29 19:12:06 by dbaldy           ###   ########.fr       */
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

static int		change_line(t_com_list **begin, t_hist_list **hist)
{
	char	*str;

	while (term_mv_horizontal(4, 0) != -1)
		;
	ft_notputs("cd", 1);
	*begin = com_list_dup((*hist)->old);
	str = com_list_retrieve(*begin);
	hist_print_line(str);
	g_local->curs = g_local->prompt + 1 +(int)ft_strlen(str);
	free(str);
	return (0);
}

static int		hist_boucle(t_hist_list **hist, char *str)
{
	char		*tmp;

	while (*hist)
	{
		tmp = com_list_retrieve((*hist)->old);
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

int			exit_search_hist(t_com_list **begin)
{
	exit_completion(*begin);
	manage_search_hist(NULL, NULL, NULL, 2);
	return (0);
}

/*
** check if search bar matches with history
*/

int			search_bar_history(t_com_list **begin, t_hist_list **hist,
		t_line *line)
{
	char					*str;
	static t_hist_list		*buf;
	int						ret;

	line_of_command(line, &str);
	if (ft_strcmp(str, "") == 0)
		*hist = buf;
	else
		buf = *hist;
	if ((ret = hist_boucle(hist, str)) == 0)
		*hist = buf;
	else
		change_line(begin, hist);
	free(str);
	return (ret);
}
