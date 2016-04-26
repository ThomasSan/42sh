/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tputs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 10:25:14 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/21 18:25:44 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	f_putchar(int c)
{
	ft_putchar_fd(c, STDIN_FILENO);
	return (0);
}

int			ft_tputs(char *s, int nb_l, int flag)
{
	char	*str[2];
	char	*term;

	str[0] = ft_memalloc(50);
	str[1] = str[0];
	term = tgetstr(s, &(str[0]));
	if (flag != 0)
		term = tgoto(term, flag, flag);
	if (flag != 0 || (s[0] > 96 && s[0] < 123))
		tputs(term, nb_l, f_putchar);
	free(str[1]);
	return (0);
}
