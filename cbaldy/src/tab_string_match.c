/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_string_match.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 18:06:35 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/24 20:00:35 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int			invert(t_param **a, t_param **b)
{
	t_param	*bufb;
	t_param	*bufa;
	
	bufb = (*b)->next;
	bufa = (*a)->prev;
	if (bufa != NULL)
		bufa->next = *b;
	(*b)->prev = bufa;
	(*b)->next = *a;
	(*a)->prev = (*b);
	(*a)->next = bufb;
	if (bufb != NULL)
		bufb->prev = *a;
	return (0);
}

static int			revert_param(t_param **a, t_param **b, t_param **debut)
{
	t_param	*temp;

	temp = *a;
	while (ft_strcmp((*b)->var, (*a)->var) < 0)
	{
		invert(a, b);
		*debut = (ft_strcmp((*a)->var, (*debut)->var) == 0) ? *b : *debut;
		*a = ((*b)->prev != NULL) ? (*b)->prev : *b;
		*b = ((*b)->prev != NULL) ? *b : (*b)->next;
	}
	*a = temp;
	*b = (*a)->next;
	return (0);
}

static t_param		*tab_class_lex(t_param **debut)
{
	t_param		*a;
	t_param		*b;

	a = *debut;	
	b = a->next;
	while (b != NULL)
	{
		if (ft_strcmp(b->var, a->var) < 0)
			revert_param(&a, &b, debut);
		else
		{
			b = b->next;
			a = a->next;
		}
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
		if (ft_strncmp(var, buf[i], size) == 0 && buf[i][0] != '.')
			tmp = add_file(debut, buf[i]);
		if (tmp && tmp->nb == 0)
			debut = tmp;
		i++;
	}
	if (tmp == NULL)
		return (NULL);
	tmp = tab_class_lex(&debut);
	debut->prev = tmp;
	tmp->next = debut;
	ft_dprintf(1, "%d\n", debut->nb);
	return (debut);
	tmp = tab_class_lex(&debut);
}
