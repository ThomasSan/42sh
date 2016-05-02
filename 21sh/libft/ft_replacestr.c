/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replacestr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/13 15:07:31 by dbaldy            #+#    #+#             */
/*   Updated: 2016/04/22 18:38:53 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_replacestr(char *old, char *to_check, char *alias)
{
	char	*ret;
	char	*buf;
	int		i;

	i = 0;
	buf = NULL;
	ret = ft_strdup(old);
	while (old[i])
	{
		if (ft_strncmp(&old[i], to_check, ft_strlen(to_check)) == 0)
		{
			if (buf != NULL)
				free(buf);
			buf = ft_strsub(ret, 0, i);
			free(ret);
			ret = ft_strjoin_multiple(3, buf, alias,
					&old[i + ft_strlen(alias)]);
		}
		i++;
	}
	free(old);
	return (ret);
}
