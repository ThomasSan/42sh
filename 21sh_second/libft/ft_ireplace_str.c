/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 15:57:00 by dbaldy            #+#    #+#             */
/*   Updated: 2016/04/29 13:58:05 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		*ft_ireplace_str(char *old, char *replace, int i, int length)
{
	char	*new;
	char	*buf;
	char	*end;

	if ((int)ft_strlen(old) < i)
		return (old);
	buf = ft_strsub(old, 0, i);
	if ((int)ft_strlen(old) >= i + length)
		end = ft_strsub(old, i + length, ft_strlen(old) - i - length);
	else
		end = ft_strdup("");
	new = ft_strjoin_multiple(3, buf, replace, end);
	free(buf);
	free(end);
	return (new);
}
