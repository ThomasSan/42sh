/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 15:57:00 by dbaldy            #+#    #+#             */
/*   Updated: 2016/04/27 12:34:50 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

char		*ft_replace_str(char *old, char *str, char *replace)
{
	char	*new;
	char	*buf;
	char	*end;

	if ((new = ft_strstr(old, str)) == NULL)
		return (ft_strdup(old));
	buf = ft_strsub(old, 0, ft_strlen(old) - ft_strlen(new));
	end = ft_strsub(old, ft_strlen(old) - ft_strlen(new) + ft_strlen(str),
			ft_strlen(buf) + ft_strlen(new));
	new = ft_strjoin_multiple(3, buf, replace, end);
	free(buf);
	free(end);
	return (new);
}
