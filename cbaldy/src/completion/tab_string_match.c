/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_string_match.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 18:06:35 by dbaldy            #+#    #+#             */
/*   Updated: 2016/05/03 19:47:23 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int			revert_param(t_param *a, t_param *b)
{
	char	*buf;

	while (a->nb > b->nb && ft_strcmp(b->var, a->var) < 0)
	{
		buf = b->var;
		b->var = a->var;
		a->var = buf;
		b = b->prev;
		a = a->prev;
	}
	return (0);
}

static t_param		*tab_class_lex(t_param *debut)
{
	t_param		*a;
	t_param		*b;

	a = debut;
	b = a->next;
	while (b->nb != 0)
	{
		if (ft_strcmp(b->var, a->var) < 0)
			revert_param(a, b);
		b = b->next;
		a = a->next;
	}
	return (a);
}

static t_param		*add_file(t_param *debut, char *str)
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

t_param				*string_matches(char *var, char **buf)
{
	size_t		size;
	int			i;
	t_param		*debut;
	t_param		*tmp;

	tmp = NULL;
	debut = NULL;
	size = ft_strlen(var);
	i = 0;
	while (buf[i])
	{
		if (ft_strcmp(var, "") != 0)
			tmp = (ft_strncmp(var, buf[i], size) == 0 && buf[i][0] != '.') ?
				add_file(debut, buf[i]) : tmp;
		else if (buf[i][0] != '.')
			tmp = add_file(debut, buf[i]);
		debut = (tmp && tmp->nb == 0) ? tmp : debut;
		i++;
	}
	if (tmp == NULL)
		return (NULL);
	debut->prev = tmp;
	tmp->next = debut;
	tab_class_lex(debut);
	return (debut);
}
