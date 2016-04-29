/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/29 16:50:34 by dbaldy            #+#    #+#             */
/*   Updated: 2016/04/29 17:19:16 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"

static char				*new_char(char *wrk, int i)
{
	char	*buf;
	char	*end;
	char	*res;

	buf = ft_strsub(wrk, 0, i);
	end = ft_strsub(wrk, i + 1, ft_strlen(wrk) - ft_strlen(buf) - 1);
	res = ft_strjoin(buf, end);
	free(buf);
	free(end);
	return (res);
}

char					*remove_quotes(char *to_glob)
{
	int			i;
	char		*buf;
	char		*wrk;
	char		c;

	i = 0;
	wrk = ft_strdup(to_glob);
	buf = NULL;
	while (wrk[i])
	{
		if (wrk[i] == 0x22 || wrk[i] == 0x27 || wrk[i] == 0x5c)
		{
			c = wrk[i];
			if (buf != NULL)
				free(buf);
			buf = new_char(wrk, i);
			free(wrk);
			wrk = ft_strdup(buf);
			i = (c == 0x5c) ? i + 1 : i - 1;
		}
		i++;
	}
	if (buf != NULL)
		free(buf);
	return (wrk);
}
