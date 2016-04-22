/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_history.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/26 19:22:58 by dbaldy            #+#    #+#             */
/*   Updated: 2016/04/22 19:37:02 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		non_empty(t_line_list *first)
{
	char	*buf;
	int		i;

	while (first->previous)
		first = first->previous;
	i = 0;
	buf = line_list_retrieve(first);
	while (buf[i])
	{
		if (buf[i] != ' ' && buf[i] != '\0')
		{
			free(buf);
			return (0);
		}
		i++;
	}
	free(buf);
	return (1);
}

static int		new_elem_hist(t_hist_list *hist, t_line_list *first)
{
	t_line_list	*tmp;

	tmp = first;
	while (tmp->next)
		tmp = tmp->next;
	while (tmp->previous)
	{
		tmp->marge = 0;
		tmp = tmp->previous;
	}
	hist->old = tmp;
	return (0);
}

t_hist_list		*retrieve_history(int flag, t_line_list *first)
{
	static t_hist_list	*hist;
	t_hist_list			*buf;

	buf = NULL;
	if (flag == 0)
	{
		hist_list_new(&buf);
		buf->next = copy_hist(hist);
		if (buf->next != NULL)
			buf->next->previous = buf;
		return (buf);
	}
	else if (flag == 2)
		return (copy_hist(hist));
	else if (non_empty(first) == 0)
	{
		hist_list_new(&hist);
		new_elem_hist(hist, first);
	}
	return (NULL);
}

static int		history_builtin_opt(char **com, int last_nb)
{
	if (com[1] && com[2])
	{
		ft_dprintf(STDERR_FILENO, "history: too many arguments\n");
		return (-1);
	}
	else if (com[1] == NULL)
		return (16);
	if (com[1][0] == '-' && ft_isdigit(com[1][1]))
		return (ft_atoi(&com[1][1]));
	else if (ft_isdigit(com[1][0]))
		return (last_nb - ft_atoi(com[1]));
	else
		ft_dprintf(STDERR_FILENO, "history: bad format\n");
	return (-1);
}

int				sh_builtin_history(char **com)
{
	t_hist_list		*buf;
	t_hist_list		*tmp;
	int				i;
	char			*str;
	int				count;

	i = -1;
	if ((buf = retrieve_history(2, NULL)) == NULL)
		return (1);
	if ((count = history_builtin_opt(com, buf->nb - 1)) == -1)
		return (1);
	tmp = buf;
	while (buf->next && i++ < count)
		buf = buf->next;
	while (buf)
	{
		str = line_list_retrieve(buf->old);
		ft_dprintf(STDOUT_FILENO, "%4d  %s\n", buf->nb, str);
		free(str);
		buf = buf->previous;
	}
	clear_hist(&tmp);
	return (0);
}
