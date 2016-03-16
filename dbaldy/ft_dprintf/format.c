/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 16:34:13 by dbaldy            #+#    #+#             */
/*   Updated: 2016/01/30 14:53:43 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*complete(char *str, int size, const char *type)
{
	char	*res;
	char	sign;

	if ((str[0] == '-' || str[0] == '+') && type[0] != ' ')
	{
		sign = str[0];
		res = ft_strsub(str, 1, ft_strlen(str) - 1);
	}
	else
	{
		sign = 0;
		res = ft_strdup(str);
	}
	free(str);
	size = (sign > 0) ? size + 2 : size + 1;
	while (size-- && size > 0)
	{
		str = res;
		res = ft_strjoin((char*)type, res);
		free(str);
	}
	if (sign > 0)
		res[0] = sign;
	return (res);
}

char			*complete_unleak(char *str, char *tmp)
{
	char	*buf;

	buf = ft_strjoin(str, tmp);
	free(str);
	str = buf;
	return (str);
}

char			*complete_behind(char *str, int size, const char *type)
{
	char	*res;

	res = ft_strdup(str);
	free(str);
	while (size-- && size > 0)
	{
		str = res;
		res = ft_strjoin(res, (char*)type);
		free(str);
	}
	return (res);
}

char			*complete_special(char *str, int size, const char *type)
{
	char	*res;
	char	sign;

	if ((str[0] == '-' || str[0] == '+' || str[0] == ' ') && type[0] != ' ')
	{
		sign = str[0];
		res = ft_strsub(str, 1, ft_strlen(str) - 1);
	}
	else
	{
		sign = 0;
		res = ft_strdup(str);
	}
	free(str);
	size = (sign > 0) ? size + 2 : size + 1;
	while (size-- && size > 0)
	{
		str = res;
		res = ft_strjoin((char*)type, res);
		free(str);
	}
	if (sign > 0)
		res[0] = sign;
	return (res);
}
