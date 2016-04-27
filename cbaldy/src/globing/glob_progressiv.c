/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_progressiv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 09:57:11 by dbaldy            #+#    #+#             */
/*   Updated: 2016/04/27 10:53:26 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"

t_glob_list			*g_glob;

static char			*build_p(char **table, int i)
{
	int		j;
	char	*tmp;
	char	*res;

	j = 0;
	res = ft_strdup("");
	while (table[j] && j <= i)
	{
		tmp = res;
		res = (ft_strcmp(res, "/") != 0 && j > 0) ? ft_strjoin_multiple(3, res,
				"/", table[j]) : ft_strjoin(res, table[j]);
		free(tmp);
		j++;
	}
	return (res);
}

static int			analyze_tab(char **to_analyze, char *match, int i)
{
	char		*buf;
	char		*to_add;

	buf = to_analyze[i + 1];
	to_analyze[i + 1] = match;
	if (to_analyze[i + 2] != NULL)
		glob_recurs(to_analyze, i + 1);
	else
	{
		to_add = build_p(to_analyze, i + 1);
		g_glob = add_elem_glob(to_add, g_glob);
		free(to_add);
	}
	to_analyze[i + 1] = buf;
	return (0);
}

int					glob_recurs(char **to_analyze, int i)
{
	char	*path;
	char	**table;
	int		j;

	path = build_p(to_analyze, i);
	if ((table = build_match_list(path, to_analyze[i + 1],
					to_analyze[i + 2])) == NULL)
	{
		free(path);
		return (-1);
	}
	j = 0;
	free(path);
	while (table[j])
	{
		analyze_tab(to_analyze, table[j], i);
		j++;
	}
	ft_free_tab(table);
	return (0);
}


t_glob_list			 *glob_progressiv(char *word)
{
	char		**to_analyze;
	
	g_glob = NULL;
	to_analyze = ft_strsplit(word, '/');
	if (*word == '/')
		ft_array_push(&to_analyze, "/");
	else if (ft_strncmp(word, "./", 2) != 0 && ft_strncmp(word, "../", 3) != 0)
		ft_array_push(&to_analyze, ".");
	glob_recurs(to_analyze, 0);
	ft_free_tab(to_analyze);
	while (g_glob && g_glob->prev)
		g_glob = g_glob->prev;
	return (g_glob);
}
