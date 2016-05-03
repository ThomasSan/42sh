/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 12:59:32 by cbaldy            #+#    #+#             */
/*   Updated: 2015/12/07 10:29:10 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*temp;
	t_list	*fresh;
	t_list	*suiv;
	t_list	*prev;

	temp = lst;
	fresh = f(temp);
	if (temp->next != NULL)
	{
		temp = temp->next;
		prev = (t_list *)malloc(sizeof(t_list));
		suiv = (t_list *)malloc(sizeof(t_list));
		prev = f(temp);
		fresh->next = prev;
		temp = temp->next;
		while (temp != NULL)
		{
			suiv = f(temp);
			prev->next = suiv;
			prev = suiv;
			temp = temp->next;
		}
	}
	return (fresh);
}
