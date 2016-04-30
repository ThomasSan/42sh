/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_spec_car.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/29 18:45:18 by dbaldy            #+#    #+#             */
/*   Updated: 2016/04/30 15:16:57 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"

int						new_char(char **wrk, int i)
{
	char	*buf;
	char	*end;
	char	*res;

	buf = ft_strsub(*wrk, 0, i);
	end = ft_strsub(*wrk, i + 1, ft_strlen(*wrk) - ft_strlen(buf) - 1);
	res = ft_strjoin(buf, end);
	free(buf);
	free(end);
	free(*wrk);
	*wrk = res;
	return (0);
}

char					*remove_spec_car(char *to_glob)
{
	int			i;
	char		*wrk;
	char		c;

	i = 0;
	wrk = ft_strdup(to_glob);
	while (wrk[i])
	{
		if (wrk[i] == 0x5c && wrk[i + 1] != '?' && wrk[i + 1] != '*' && 
				wrk[i + 1] != '[' && wrk[i + 1] != ']')
		{
			c = wrk[i];
			new_char(&wrk, i);
			i = (c == 0x5c) ? i + 1 : i - 1;
		}
		i++;
	}
	return (wrk);
}
