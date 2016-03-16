/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   longchar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 11:19:18 by dbaldy            #+#    #+#             */
/*   Updated: 2016/01/22 15:45:00 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*replace_end(char *str, char c)
{
	char	*tmp;
	char	*buf;

	if (str[ft_strlen(str) - 1] == c)
	{
		tmp = ft_strsub(str, 0, ft_strlen(str) - 1);
		buf = str;
		str = ft_strjoin(tmp, "l0");
		str[ft_strlen(str) - 1] = ft_tolower(c);
		free(buf);
		free(tmp);
	}
	return (str);
}

char		*treatwint(wint_t c)
{
	char	*str;

	str = initialize_str(c);
	if (c < 0x80)
		str[0] = c & 0b01111111;
	else if (c < 0x800)
	{
		str[1] = c & 0b00111111;
		str[1] = str[1] | 0b10000000;
		c >>= 6;
		str[0] = c & 0b00011111;
		str[0] += 0b11000000;
	}
	else
	{
		str[2] = c & 0b00111111;
		str[2] = str[2] | 0b10000000;
		c >>= 6;
		str[1] = c & 0b00111111;
		str[1] = str[1] | 0b10000000;
		c >>= 6;
		str[0] = c & 0b00001111;
		str[0] = str[0] | 0b11100000;
	}
	return (str);
}

char		*initialize_str(wint_t c)
{
	int		size;
	int		hex;
	char	*str;

	size = 1;
	hex = 0x80;
	while (c)
	{
		size++;
		c /= hex;
	}
	if ((str = (char*)malloc(sizeof(unsigned char) * size)) == NULL)
		exit(1);
	while (size-- >= 0)
		str[size] = 0;
	return (str);
}
