/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suppr_elem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 13:59:00 by dbaldy            #+#    #+#             */
/*   Updated: 2016/04/02 17:13:05 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int				print_line(t_line *line)
{
	t_line	*buf;

	buf = line;
	while (buf)
	{
		if (buf->select == 1)
			ft_notputs("us", 1);
		ft_dprintf(STDOUT_FILENO, "%c", buf->c);
		if (buf->select == 1)
			ft_notputs("ue", 1);
		buf = buf->next;
	}
	return (0);
}

int				clear_tline(t_line **elem)
{
	t_line	*buf;
	t_line	*a;

	if (*elem == NULL)
		return (0);
	buf = *elem;
	if (buf->prev != NULL)
		buf->prev->next = NULL;
	while (buf)
	{
		a = buf->next;
		buf->next = NULL;
		buf->prev = NULL;
		free(buf);
		buf = a;
	}
	*elem = NULL;
	return (0);
}
int				line_of_command(t_line *debut, char **str)
{
	t_line	*buf;
	int		size;
	char	*ret;
	int		i;

	i = 0;
	size = 0;
	buf = debut;
	while (buf)
	{
		buf = buf->next;
		size++;
	}
	if ((ret = (char*)malloc(sizeof(char) * (size + 1))) == NULL)
		return (-1);
	buf = debut;
	while (buf)
	{
		ret[i] = buf->c;
		i++;
		buf = buf->next;
	}
	ret[i] = '\0';
	*str = ret;
	return (0);
}

static int			decrease_nb(t_line *buf)
{
	while (buf)
	{
		buf->nb -= 1;
		buf = buf->next;
	}
	return (0);
}

int					suppr_char_list(t_line **chaine)
{
	t_line		*buf;

	buf = *chaine;
	if (buf->select == 1 && buf->prev == NULL)
		return (0);
	while (buf && buf->next && buf->next->select == 0)
		buf = buf->next;
	decrease_nb(buf->next);
	if (buf->prev == NULL)
	{
		*chaine = buf->next;
		(*chaine)->prev = NULL;
	}
	else
	{
		buf->prev->next = buf->next;
		buf->next->prev = buf->prev;
	}
	free(buf);
	return (0);
}
