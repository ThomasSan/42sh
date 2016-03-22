/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 17:15:28 by tsanzey           #+#    #+#             */
/*   Updated: 2015/11/30 17:33:39 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*dup;
	int		i;

	i = 0;
	dup = ft_strnew(ft_strlen(s));
	while (s[i])
	{
		dup[i] = f(s[i]);
		i++;
	}
	return (dup);
}
