/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_supp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 15:14:39 by dbaldy            #+#    #+#             */
/*   Updated: 2016/04/25 16:06:42 by dbaldy           ###   ########.fr       */
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
	new->select = (buf == NULL) ? 2 : 0;
	return (new);
}

int			iscommand(char *var, int marge)
{
	int		i;
	int		curseur;

	curseur = g_local->curs - marge - 1;
	i = 0;
	while (var[i] && i < curseur && var[i] <= ' ')
		i++;
	while (var[i] && i < curseur)
	{
		if (var[i] == ' ' || var[i] == '/')
			return (1);
		i++;
	}
	if (i > 0 && var[i - 1] == '/')
		return (1);
	return (0);
}

int			fputchar(int c)
{
	ft_putchar_fd(c, STDIN_FILENO);
	return (0);
}
