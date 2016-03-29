/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_mode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 13:40:47 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/29 17:08:06 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char			**hash_table(char **hash)
{
	int		i;
	char	**res;

	i = 0;
	while (hash[i])
		i++;
	if ((res = (char**)malloc(sizeof(char*) * (i + 1))) == NULL)
		return (NULL);
	i = 0;
	while (hash[i])
	{
		res[i] = ft_strtrunc(hash[i], '=');
		i++;
	}
	res[i] = NULL;
	return (res);
}

static char			*word_to_tab(char *var)
{
	char		*res;
	char		*buf;

	res = path_to_tab(var);
	buf = (ft_strrchr(res, '/') != NULL) ? ft_strdup(ft_strrchr(res, '/') + 1)
		: ft_strdup(res);
	free(res);
	return (buf);
}

int					tab_mode(t_com_list *begin)
{
	t_param				*debut;
	char				*var;
	char				**table;
	char				*word;

	if (begin == NULL)
		return (0);
	if (g_curr_compl != NULL)
		return (tab_complete_line(g_curr_compl->begin, begin,
			g_curr_compl->var));
		if ((var = com_list_retrieve(begin)) == NULL)
		return (0);
	table = (iscommand(var) == 0) ? hash_table(g_hash) : list_path(var);
	if (table == NULL)
		return (0);
	word = word_to_tab(var);
	if ((debut = string_matches(word, table)) == NULL && g_curr_compl != NULL)
		exit_completion(begin);
	else if (debut != NULL)
		tab_select(&debut, begin, word);
	ft_free_tab(table);
	free(var);
	free(word);
	return (0);
}
