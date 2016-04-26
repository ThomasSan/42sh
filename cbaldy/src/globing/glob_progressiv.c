/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_progressiv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 09:57:11 by dbaldy            #+#    #+#             */
/*   Updated: 2016/04/26 14:50:41 by dbaldy           ###   ########.fr       */
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

static int			glob_recurs(char **to_analyze, int i)
{
	char	*path;
	char	**table;
	int		j;

	if (ft_strcmp(to_analyze[0], "/") == 0 && i == 0)
		i++;
	path = build_p(to_analyze, i);
	ft_printf("path: %s\n", path);
	if ((table = build_match_list(path, to_analyze[i + 1],
					to_analyze[i + 2])) == NULL)
	{
		free(path);
		return (-1);
	}
	j = 0;
	while (table[j])
	{
		if (to_analyze[i + 2] != NULL)
		{
			ft_printf("to_analyze:%s\n", to_analyze[i + 2]);
			to_analyze[i + 1] = table[j];
			glob_recurs(to_analyze, i + 1);
		}
		else
			add_elem_glob(build_p(to_analyze, i + 1), g_glob);
		j++;
	}
	return (0);
}


t_glob_list			 *glob_progressiv(char *word)
{
	char		**to_analyze;

	to_analyze = ft_strsplit(word, '/');
	if (*word == '/')
		ft_array_push(&to_analyze, "/");
	glob_recurs(to_analyze, 0);
	return (g_glob);
}
