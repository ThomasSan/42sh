/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suppr_elem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 13:59:00 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/29 14:55:06 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

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
