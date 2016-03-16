/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 14:41:01 by dbaldy            #+#    #+#             */
/*   Updated: 2015/11/30 12:16:35 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*buf;
	t_list	*new;

	buf = f(lst);
	new = buf;
	while (lst->next)
	{
		lst = lst->next;
		buf->next = f(lst);
		buf = buf->next;
	}
	return (new);
}
