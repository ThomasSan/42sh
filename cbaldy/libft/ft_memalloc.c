/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 10:08:42 by cbaldy            #+#    #+#             */
/*   Updated: 2015/11/30 19:17:56 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = malloc(size);
	if (ptr == NULL)
		return (NULL);
	else
		while (i < size)
		{
			ptr[i] = '\0';
			i++;
		}
	return ((void *)ptr);
}
