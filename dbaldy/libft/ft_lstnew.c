/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 19:53:47 by dbaldy            #+#    #+#             */
/*   Updated: 2015/11/30 12:24:18 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list		*s1;

	s1 = (t_list *)malloc(sizeof(t_list));
	if (s1 == NULL)
		return (NULL);
	if (content == NULL)
	{
		s1->content = NULL;
		s1->content_size = 0;
		s1->next = NULL;
	}
	else
	{
		s1->content = malloc(sizeof(content_size));
		s1->content = ft_memcpy(s1->content, content, content_size);
		s1->content_size = content_size;
		s1->next = NULL;
	}
	return (s1);
}
