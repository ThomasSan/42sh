/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 17:00:28 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/23 10:53:08 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	print_return_cursor(int len_str)
{
	while (len_str > 0)
	{
		term_mv_horizontal(4, 0);
		len_str--;
	}
	return (0);
}

int			print_command(t_com_list *new, char buf)
{
	char	*str;
	int		len_str;
	int		op;

	ft_tputs("vi", 1, 0);
	op = (buf == 127 ? 0 : 1);
	str = com_list_retrieve(new);
	if (buf == 127)
		term_mv_horizontal(4, 0);
	ft_putstr_fd(str, STDIN_FILENO);
	len_str = ft_strlen(str);
	g_local->curs += len_str;
	if (g_local->curs % g_local->nb_col == 1 && len_str > 1)
		ft_tputs("sf", 1, 0);
	else if (g_local->curs % g_local->nb_col == 1 && len_str == 1)
		ft_tputs("sf", 1, 0);
	ft_tputs("ce", 1, 0);
	print_return_cursor(ft_strlen(str) - op);
	free(str);
	ft_tputs("ve", 1, 0);
	return (buf);
}
