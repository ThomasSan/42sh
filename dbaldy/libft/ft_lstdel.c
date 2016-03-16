/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 14:31:01 by dbaldy            #+#    #+#             */
/*   Updated: 2015/11/30 12:15:10 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*temp;
	t_list	*buf;

	temp = *alst;
	while (temp != NULL)
	{
		buf = temp->next;
		ft_lstdelone(&temp, (del));
		temp = buf;
	}
	*alst = NULL;
}
