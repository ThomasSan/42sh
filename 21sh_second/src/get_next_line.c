/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 18:10:15 by cbaldy            #+#    #+#             */
/*   Updated: 2016/02/29 19:39:35 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		strlen_n(char *str)
{
	int		k;

	k = 0;
	while (str[k] != '\0')
	{
		if (str[k] == '\n')
		{
			k++;
			return (k);
		}
		k++;
	}
	return (k);
}

static int		read_file(int const fd, char **line, char **stock)
{
	int			i;
	char		*buf[2];
	char		*sol;

	buf[0] = ft_strnew(BUFF_SIZE);
	if ((i = read(fd, buf[0], BUFF_SIZE)) <= 0)
	{
		free(buf[0]);
		return (i);
	}
	sol = ft_strsub(buf[0], 0, strlen_n(buf[0]));
	if (sol[ft_strlen(sol) - 1] == '\n')
		*stock = ft_strdup(&(ft_strchr(buf[0], '\n')[1]));
	if (*line == NULL)
		*line = sol;
	else
	{
		buf[1] = ft_strjoin(*line, sol);
		free(*line);
		free(sol);
		*line = ft_strdup(buf[1]);
		free(buf[1]);
	}
	free(buf[0]);
	return (i);
}

static int		is_stock_empty(char **stock, char **line)
{
	char		*tmp[2];
	int			i;

	i = 0;
	if (*stock != NULL)
	{
		tmp[0] = ft_strsub(*stock, 0, strlen_n(*stock));
		if (ft_strchr(*stock, '\n') != NULL)
		{
			tmp[1] = *stock;
			*stock = ft_strdup(&(ft_strchr(*stock, '\n')[1]));
			free(tmp[1]);
		}
		else
		{
			free(*stock);
			*stock = NULL;
		}
		i = (tmp[0][ft_strlen(tmp[0]) - 1] == '\n' ? 1 : 0);
		*line = ft_strsub(tmp[0], 0, ft_strlen(tmp[0]) - i);
		free(tmp[0]);
	}
	else
		*line = NULL;
	return (i);
}

int				get_next_line(int const fd, char **line)
{
	int			i[3];
	static char	*stock;

	if (line == NULL)
		return (-1);
	if ((i[1] = is_stock_empty(&stock, line)) == 1)
		return (1);
	i[1] = 1;
	i[2] = 0;
	while (i[1] != 0)
	{
		if ((i[0] = read_file(fd, line, &stock)) <= 0)
			return (i[2] == 0 ? i[1] : i[2]);
		else
			i[2] = 1;
		if (line[0][ft_strlen(*line) - 1] == '\n')
		{
			i[1] = 0;
			line[0][ft_strlen(*line) - 1] = '\0';
		}
	}
	return (1);
}
