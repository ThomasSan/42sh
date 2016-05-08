/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/29 13:46:46 by cbaldy            #+#    #+#             */
/*   Updated: 2016/05/08 17:30:35 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_dprintf(int fd, char *str, ...)
{
	va_list ap;
	int		i;
	int		count;

	count = 0;
	i = 0;
	va_start(ap, str);
	while (str[i] != '\0')
	{
		if (str[i] != '%')
		{
			count++;
			write(fd, &(str[i]), 1);
		}
		else
		{
			count += ft_convert(str, ap, i, fd);
			i += ft_len_opt(&(str[i])) - 1;
		}
		i++;
	}
	va_end(ap);
	return (count);
}
