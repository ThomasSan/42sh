/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_intab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 12:41:14 by tsanzey           #+#    #+#             */
/*   Updated: 2016/04/25 12:49:29 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_parse		*ft_push_in_tab(t_parse *new, t_token *tok)
{
	int		rows;
	int		i;

	i = 0;
	rows = number_of_rows(tok);
	if (!(new->arg = (char **)malloc(sizeof(char *) * rows + 1)))
		return (NULL);
	while (i < rows)
	{
		new->arg[i] = ft_strdup(tok->content);
		tok = tok->next;
		i++;
	}
	new->arg[i] = NULL;
	new->type = CMD;
	return (new);
}
