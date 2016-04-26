/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_douprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/15 16:15:06 by cbaldy            #+#    #+#             */
/*   Updated: 2016/01/28 17:55:24 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_douprint(va_list ap2)
{
	if (g_op->c == 'D')
	{
		g_op->size = 3;
		return (ft_print_z(ap2));
	}
	else if (g_op->c == 'O' || g_op->c == 'U')
	{
		g_op->size = 4;
		g_op->c = (g_op->c == 'O' ? 'o' : 'u');
		return (ft_print_uz(ap2));
	}
	return (0);
}
