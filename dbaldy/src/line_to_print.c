/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 15:50:24 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/14 18:04:29 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			size_tline(t_line *buf, int type)
{
	int		size;

	size = 0;
	while (buf->next)
	{
		size++;
		buf = buf->next;
	}
	return ((type == 0) ? size : buf->nb);
}

int			get_string(t_line *buf, char **ret)
{
	int		i;

	i = 0;
	if ((*ret = (char*)malloc(sizeof(char) * (size_tline(buf, 0) + 1))) == NULL)
		return (-1);
	while (buf->next)
	{
		(*ret)[i] = buf->c;
		i++;
		buf = buf->next;
	}
	(*ret)[i] = '\0';
	return (0);
}

int			replace_cursor(int *x, int *y)
{
	ft_tputs("vi", 1);
	if (x[1] == 0)
		ft_tputs("sf", 1);
	if (y[1] - y[0] != 0)
		ft_tputs("up", y[1] - y[0]);
	if (x[1] - x[0] > 0)
		ft_tputs("le", x[1] - x[0]);
	else if (x[1] - x[0] < 0)
		ft_tputs("nd", x[0] - x[1]);
	ft_tputs("ve", 1);
	return (0);
}

int			line_to_print(t_line *ok)
{
	char	*str;
	int		x[2];
	int		y[2];

	x[0] = (ok->nb + (int)ft_strlen(g_prompt) + 1) % get_width();
	y[0] = (ok->nb + (int)ft_strlen(g_prompt) + 1) / get_width();
	x[1] = (ok->nb + size_tline(ok, 0) +
			(int)ft_strlen(g_prompt)) % get_width();
	y[1] = (ok->nb + size_tline(ok, 0) +
			(int)ft_strlen(g_prompt)) / get_width();
	get_string(ok, &str);
	ft_putstr_fd(str, get_fd(0));
	ft_tputs("cd", 1);
	replace_cursor(x, y);
	free(str);
	return (0);
}
