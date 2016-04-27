/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_modif_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 18:48:50 by dbaldy            #+#    #+#             */
/*   Updated: 2016/04/27 16:14:40 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"

static int		add_bckslsh(char **to_add)
{
	int		i;
	char	*tmp;
	char	*begin;
	char	*end;

	i = 0;
	while ((*to_add)[i])
	{
		if ((*to_add)[i] == ' ')
		{
			begin = ft_strsub(*to_add, 0, i);
			end = ft_strdup(&((*to_add)[i]));
			tmp = ft_strjoin_multiple(3, begin, "\x5c", end);
			free(begin);
			free(end);
			free(*to_add);
			*to_add = tmp;
			i += 1;
		}
		i++;
	}
	return (0);
}

static char		*full_glob(t_glob_list *match_list, char *word)
{
	char		*tmp;
	t_glob_list *l_buf;
	char		*insert;
	char		*to_add;

	l_buf = match_list;
	insert = ft_strdup("");
	while (l_buf)
	{
		tmp = ft_strdup(insert);
		free(insert);
		if (ft_strncmp(word, "./", 2) && ft_strncmp(l_buf->var, "./", 2) == 0)
			to_add = ft_strsub(l_buf->var, 2, ft_strlen(l_buf->var) - 2);
		else
			to_add = ft_strdup(l_buf->var);
		if (ft_strchr(to_add, ' ') != NULL)
			add_bckslsh(&to_add);
		insert = (ft_strcmp(tmp, "") == 0) ? ft_strdup(to_add) :
			ft_strjoin_multiple(3, tmp, " ", to_add);
		free(to_add);
		free(tmp);
		l_buf = l_buf->next;
	}
	return (insert);
}

int				glob_modif_str(char **str, t_glob_list *match_list, char *word
		, int *i)
{
	char		*insert;
	char		*tmp;

	insert = full_glob(match_list, word);
	tmp = ft_replace_str(*str, word, insert);
	free(*str);
	*str = tmp;
	*i = ft_strlen(*str) - ft_strlen((ft_strstr(*str, insert) +
				ft_strlen(insert)));
	free(insert);
	return (0);
}
