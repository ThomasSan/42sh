/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 10:53:18 by dbaldy            #+#    #+#             */
/*   Updated: 2016/02/17 10:43:15 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strnew(size_t size)
{
	size_t	i;
	char	*s1;

	i = 0;
	s1 = (char*)malloc(size + 1);
	if (s1 == NULL)
		return (NULL);
	while (i < size + 1)
	{
		s1[i] = '\0';
		i++;
	}
	return (s1);
}
