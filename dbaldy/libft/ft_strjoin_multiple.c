/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_multiple.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 15:49:47 by dbaldy            #+#    #+#             */
/*   Updated: 2016/02/13 15:44:57 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

char			*ft_strjoin_multiple(int nb, ...)
{
	va_list ap;
	char	*ret;
	char	*buf;
	char	*str;
	int		i;

	i = 0;
	buf = ft_strdup("");
	va_start(ap, nb);
	while (i < nb)
	{
		str = va_arg(ap, char*);
		ret = ft_strjoin(buf, str);
		free(buf);
		buf = ret;
		i++;
	}
	va_end(ap);
	return (ret);
}
