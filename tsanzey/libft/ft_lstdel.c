/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 15:56:59 by tsanzey           #+#    #+#             */
/*   Updated: 2015/12/03 16:33:04 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list	*tmp;
	t_list	*nxt;

	tmp = *alst;
	if (alst)
	{
		while (tmp)
		{
			nxt = tmp->next;
			ft_lstdelone(&tmp, del);
			tmp = nxt;
		}
		*alst = NULL;
	}
}
