/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 17:45:30 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/25 16:16:38 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int			get_width(void)
{
	struct winsize	win;

	if (ioctl(STDERR_FILENO, TIOCGWINSZ, &win) < 0)
		return (0);
	return (win.ws_col);
}

int			get_height(void)
{
	struct winsize	win;

	if (ioctl(STDERR_FILENO, TIOCGWINSZ, &win) < 0)
		return (0);
	return (win.ws_row);
}

static int	mesure_size(t_param *debut)
{
	t_param	*buf;
	size_t	max;

	buf = debut;
	max = ft_strlen(buf->var);
	buf = buf->next;
	while (buf->nb > 0)
	{
		if (max < ft_strlen(buf->var))
			max = ft_strlen(buf->var);
		buf = buf->next;
	}
	return (max);
}

int			get_nb_tab(t_param *debut)
{
	int		size_max;

	size_max = mesure_size(debut);
	return (size_max / 8 + 1);
}

int			get_nb_col(t_param *debut)
{
	int		ret;
	int		width;
	int		size_max;

	width = get_width();
	size_max = mesure_size(debut);
	ret = width / (size_max + 8 - (size_max % 8));
	return ((ret > 0) ? ret : 1);
}
