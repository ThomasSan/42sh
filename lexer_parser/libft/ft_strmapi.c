/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 10:51:08 by tsanzey           #+#    #+#             */
/*   Updated: 2015/11/30 17:34:21 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*dup;
	unsigned int	i;
	unsigned int	index;

	i = 0;
	index = 0;
	dup = ft_strnew(ft_strlen(s));
	while (s[i])
	{
		dup[i] = f(index, s[i]);
		index++;
		i++;
	}
	return (dup);
}
