/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 12:23:25 by cbaldy            #+#    #+#             */
/*   Updated: 2015/11/29 15:43:07 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*tmp;
	t_list	*buf;

	tmp = (*alst)->next;
	ft_lstdelone(alst, del);
	while (tmp != NULL)
	{
		buf = tmp->next;
		ft_lstdelone(&tmp, del);
		tmp = buf;
	}
}
