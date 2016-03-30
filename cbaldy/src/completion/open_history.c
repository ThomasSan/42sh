/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 13:33:15 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/29 18:47:41 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include <string.h>

int			increase_nb(t_line *buf)
{
	while (buf)
	{
		buf->nb += 1;
		buf = buf->next;
	}
	return (0);
}

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

int				print_line(t_line *line)
{
	t_line	*buf;

	buf = line;
	while (buf)
	{
		if (buf->select == 1)
			ft_tputs("us", 1);
		ft_dprintf(get_fd(0), "%c", buf->c);
		if (buf->select == 1)
			ft_tputs("ue", 1);
		buf = buf->next;
	}
	return (0);
}

int				change_select(t_param *debut, t_line *line)
{
	t_param	*buf;
	char	*str;

	buf = debut;
	line_of_command(line, &str);
	while (buf->nb >= 0)
	{
		if (ft_strstr(buf->var, str) != NULL)
		{
			buf->select = ((buf->select % 2) == 1) ? buf->select :
				buf->select + 1;
		}
		else
			buf->select = ((buf->select % 2) == 1) ? buf->select - 1 :
				buf->select;
		buf = buf->next;
		if (buf->nb == 0)
			break ;
	}
	free(str);
	return (0);
}

int				multi_select(t_param *debut, t_line *line)
{
	t_param	*buf;
	char	*str;

	buf = debut;
	line_of_command(line, &str);
	while (buf->nb >= 0)
	{
		if ((buf->select % 2) == 1)
			buf->select = ((buf->select / 2) == 0) ? buf->select + 2 :
				buf->select - 2;
		buf = buf->next;
		if (buf->nb == 0)
			break ;
	}
	free(str);
	return (0);
}

int				open_history(int nb_row, int check, t_param *debut)
{
	static int i;

	if (check == 1 && i != 0)
		return (1);
	else if (check == 1)
		return (0);
	else if (i != 0 && manage_hist(NULL, debut, 0, 2) == 0)
	{
		i = 0;
		ft_tputs("do", nb_row);
		ft_tputs("cd", 1);
		ft_tputs("up", nb_row);
	}
	else
	{
		manage_hist("", debut, nb_row, 0);
		i++;
	}
	return (0);
}
