/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strechr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/30 15:28:17 by dbaldy            #+#    #+#             */
/*   Updated: 2016/04/30 15:28:56 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strechr(const char *s, int c)
{
	int		k;

	k = 0;
	while (s[k])
	{
		if (s[k] == 0x5c && s[k] != '\0')
			k += 2;
		else if (s[k] == c)
			return (&((char *)s)[k]);
		else
			k++;
	}
	if (c == 0)
		return (&((char *)s)[k]);
	else
		return (NULL);
}
