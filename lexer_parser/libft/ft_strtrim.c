/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 12:18:18 by tsanzey           #+#    #+#             */
/*   Updated: 2015/12/01 14:26:01 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrim(char const *s)
{
	unsigned int	i;
	unsigned int	l;
	unsigned int	k;
	char			*str;

	i = 0;
	if ((l = ft_strlen(s)) == 0)
		return ("");
	while ((s[i] == ' ' || s[i] == '\n' || s[i] == '\t') && s[i])
		i++;
	if (!(str = (char *)malloc(sizeof(str) * (l - i + 1))))
		return (NULL);
	l--;
	while ((s[l] == ' ' || s[l] == '\n' || s[l] == '\t') && l > 0)
		l--;
	k = 0;
	while ((i + k) <= l)
	{
		str[k] = s[i + k];
		k++;
	}
	str[k] = '\0';
	return (str);
}
