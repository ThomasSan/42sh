/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrunc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 12:15:58 by dbaldy            #+#    #+#             */
/*   Updated: 2016/02/13 12:46:57 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrunc(char *str, int c)
{
	char			*ret;
	int				trunc;
	char			*buf;

	if ((buf = (char*)malloc(sizeof(char) * 2)) == NULL)
		exit(1);
	buf[0] = (char)c;
	buf[1] = '\0';
	if (ft_strcmp(str, buf) == 0)
	{
		free(buf);
		return (ft_strdup(str));
	}
	free(buf);
	trunc = (ft_strchr(str, c) != NULL) ? ft_strlen(ft_strrchr(str, c)) : 0;
	trunc = ((size_t)trunc == ft_strlen(str)) ? trunc - 1 : trunc;
	ret = ft_strsub(str, 0, ft_strlen(str) - trunc);
	return (ret);
}
