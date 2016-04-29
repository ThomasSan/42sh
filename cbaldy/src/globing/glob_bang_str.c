/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_bang_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 13:54:18 by dbaldy            #+#    #+#             */
/*   Updated: 2016/04/29 10:28:04 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"

static char			*to_strstrhist(t_hist_list **hist, char *to_search)
{
	t_hist_list		*buf;
	char			*to_add;

	if ((buf = *hist) == NULL)
		return (NULL);
	while (buf)
	{
		to_add = line_list_retrieve(buf->old);
		if (ft_strstr(to_add, to_search) != NULL)
			break ;
		free(to_add);
		to_add = NULL;
		buf = buf->next;
	}
	clear_hist(hist);
	return (to_add);
}

static char			*to_strncmphist(t_hist_list **hist, char *to_search)
{
	t_hist_list		*buf;
	char			*to_add;

	if ((buf = *hist) == NULL)
		return (NULL);
	while (buf)
	{
		to_add = line_list_retrieve(buf->old);
		if (ft_strncmp(to_add, to_search, ft_strlen(to_search)) == 0)
			break ;
		free(to_add);
		to_add = NULL;
		buf = buf->next;
	}
	clear_hist(hist);
	return (to_add);
}

int					strstr_cmd(char **str, int *i, t_hist_list **hist)
{
	int			j;
	char		*to_search;
	char		*to_add;
	char		*tmp;

	j = *i + 2;
	while ((*str)[j] && (*str)[j] != ' ' && (*str)[j] != '?')
		j++;
	to_search = ft_strsub(*str, *i + 2, j - *i - 2);
	if ((to_add = to_strstrhist(hist, to_search)) == NULL)
	{
		free(to_search);
		return (-1);
	}
	tmp = ft_ireplace_str(*str, to_add, *i, ft_strlen(to_search) + 2);
	*i = ft_strlen(to_search) + 2;
	free(to_add);
	free(to_search);
	free(*str);
	*str = tmp;
	return (0);
}

int					strcmp_cmd(char **str, int *i, t_hist_list **hist)
{
	int			j;
	char		*to_search;
	char		*to_add;
	char		*tmp;

	j = *i + 2;
	while ((*str)[j] && (*str)[j] != ' ' && (*str)[j] != '?')
		j++;
	to_search = ft_strsub(*str, *i + 2, j - *i - 2);
	if ((to_add = to_strncmphist(hist, to_search)) == NULL)
	{
		free(to_search);
		return (-1);
	}
	tmp = ft_ireplace_str(*str, to_add, *i, ft_strlen(to_search) + 2);
	*i = ft_strlen(to_search) + 2;
	free(to_add);
	free(to_search);
	free(*str);
	*str = tmp;
	return (0);
}
