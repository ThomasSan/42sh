/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 13:41:50 by dbaldy            #+#    #+#             */
/*   Updated: 2016/02/17 10:44:59 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_lc				*list_clear(t_lc **begin, int fd)
{
	t_lc	*buf;
	t_lc	*temp;

	buf = *begin;
	temp = buf->next;
	if (buf->fno == fd)
	{
		*begin = (*begin)->next;
		free((buf)->str);
		free(buf);
	}
	while (temp)
	{
		if (temp->fno == fd)
		{
			free(temp->str);
			buf->next = temp->next;
			temp->next = NULL;
			free(temp);
		}
		buf = buf->next;
		temp = temp->next;
	}
	return (NULL);
}

t_lc				*scan(int fd, int type)
{
	static t_lc		*lc_begin;
	t_lc			*temp;
	t_lc			*new;

	temp = lc_begin;
	if (type == 1)
		return (list_clear(&lc_begin, fd));
	while (temp)
	{
		if (temp->fno == fd)
			return (temp);
		temp = temp->next;
	}
	if ((new = (t_lc*)malloc(sizeof(t_lc))) == NULL)
		return (NULL);
	new->next = lc_begin;
	lc_begin = new;
	new->fno = fd;
	new->str = ft_strdup("");
	return (new);
}

static int			ft_check(t_lc *obj, char **res)
{
	int			size;
	char		*temp;

	temp = ft_strdup(obj->str);
	if (ft_strchr(temp, '\n') != NULL)
	{
		size = ft_strlen(temp) - ft_strlen(ft_strchr(temp, '\n'));
		*res = ft_strsub(temp, 0, size);
		free(obj->str);
		obj->str = ft_strdup(ft_strchr(temp, '\n') + 1);
		free(temp);
		return (1);
	}
	*res = obj->str;
	free(temp);
	return (0);
}

static int			read_line(t_lc *obj, char *buf, char **line)
{
	int			size;
	char		*temp;

	size = BUFF_SIZE;
	while (size == BUFF_SIZE)
	{
		if ((size = read(obj->fno, buf, BUFF_SIZE)) == -1)
			return (-1);
		buf[BUFF_SIZE] = '\0';
		if (size < BUFF_SIZE)
			ft_strclr(&buf[size]);
		temp = ft_strjoin(obj->str, buf);
		free(obj->str);
		obj->str = temp;
		if (ft_check(obj, line) == 1)
			return (1);
	}
	*line = ft_strdup(obj->str);
	scan(obj->fno, 1);
	return (0);
}

int					get_next_line(int const fd, char **line)
{
	t_lc		*obj;
	char		*buf;
	int			ret;

	buf = NULL;
	if ((line == NULL) || (obj = scan(fd, 0)) == NULL)
		return (-1);
	if (ft_check(obj, line) == 1)
		return (1);
	if ((buf = ft_strnew(BUFF_SIZE + 1)) == NULL)
		return (-1);
	ret = read_line(obj, buf, line);
	free(buf);
	return (ret);
}
