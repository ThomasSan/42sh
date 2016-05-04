/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_bang_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 12:27:47 by dbaldy            #+#    #+#             */
/*   Updated: 2016/04/30 17:15:29 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"

static char			*to_nhist(t_hist_list **hist, int h_nb)
{
	t_hist_list		*buf;
	char			*to_add;

	if ((buf = *hist) == NULL)
		return (NULL);
	if (buf->nb < h_nb)
	{
		clear_hist(hist);
		return (NULL);
	}
	to_add = NULL;
	while (buf)
	{
		if (h_nb == buf->nb)
		{
			to_add = line_list_retrieve(buf->old);
			break ;
		}
		buf = buf->next;
	}
	clear_hist(hist);
	return (to_add);
}

int					direct_digit(char **str, int *i, t_hist_list **hist)
{
	char		*to_add;
	int			size;
	char		*tmp;

	if ((*str)[*i + 1] == '!')
	{
		size = 2;
		to_add = to_nhist(hist, (*hist)->nb);
	}
	else
	{
		size = ft_number_size(&((*str)[*i + 1])) + 1;
		to_add = to_nhist(hist, ft_atoi(&((*str)[*i + 1])));
	}
	if (to_add == NULL)
		return (-1);
	tmp = ft_ireplace_str(*str, to_add, *i, size);
	free(to_add);
	*i += size;
	free(*str);
	*str = tmp;
	return (0);
}

int					backward_digit(char **str, int *i, t_hist_list **hist)
{
	char		*to_add;
	int			size;
	char		*tmp;

	size = ft_number_size(&((*str)[*i + 2])) + 2;
	to_add = to_nhist(hist, (*hist)->nb - ft_atoi(&((*str)[*i + 2])) + 1);
	if (to_add == NULL)
		return (-1);
	tmp = ft_ireplace_str(*str, to_add, *i, size);
	free(to_add);
	*i += size;
	free(*str);
	*str = tmp;
	return (0);
}
