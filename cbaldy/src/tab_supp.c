/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_supp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 15:14:39 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/21 19:09:16 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_param		*add_file(t_param *debut, char *str)
{
	t_param		*buf;
	t_param		*new;

	buf = debut;
	while (buf && buf->next)
		buf = buf->next;
	if ((new = (t_param*)malloc(sizeof(t_param))) == NULL)
		return (NULL);
	new->var = ft_strdup(str);
	new->next = NULL;
	new->prev = buf;
	if (buf != NULL)
	{
		buf->next = new;
		new->nb = buf->nb + 1;
	}
	else
		new->nb = 0;
	new->select = (buf == NULL) ? 1 : 0;
	return ((buf == NULL) ? new : debut);
}

char		*com_list_string(t_com_list *begin)
{
	int			size;
	char		*buf;
	char		*new;

	buf = com_list_retrieve(begin);
	size = g_local->curs - g_local->prompt;
	while (buf[size] && buf[size] != ' ')
		size++;
	new = (size <= 0) ? NULL : ft_strsub(buf, 0, size);
	free(buf);
	return (new);
}
