/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_mode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 13:40:47 by cbaldy            #+#    #+#             */
/*   Updated: 2016/05/03 17:45:04 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char			**hash_table(void)
{
	int		i;
	char	**res;
	char	**hash;

	i = 0;
	if (g_hash != NULL)
	{
		ft_free_tab(g_hash);
		g_hash = NULL;
	}
	if ((hash = hash_get_tab()) == NULL)
		return (NULL);
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

static char			*word_to_tab(char *var, int marge)
{
	char		*res;
	char		*buf;

	if ((res = path_to_tab(var, marge)) == NULL)
		return (NULL);
	buf = (ft_strrchr(res, '/') != NULL) ? ft_strdup(ft_strrchr(res, '/') + 1)
		: ft_strdup(res);
	free(res);
	return (buf);
}

static int			f_var(char *var)
{
	free(var);
	return (0);
}

int					tab_mode(t_line_list **first)
{
	t_param				*debut;
	char				*var;
	char				**table;
	char				*word;

	if ((*first)->begin == NULL)
		return (0);
	if (g_curr_compl != NULL)
		return (tab_complete_line(g_curr_compl->debut, first,
			g_curr_compl->var));
		if ((var = com_list_retrieve((*first)->begin)) == NULL)
		return (0);
	table = (iscommand(var, (*first)->marge) == 0) ? hash_table() :
		list_path(var, (*first)->marge);
	word = word_to_tab(var, (*first)->marge);
	if (table == NULL || word == NULL)
		return (f_var(var));
	if ((debut = string_matches(word, table)) == NULL && g_curr_compl != NULL)
		exit_completion(*first);
	else if (debut != NULL)
		tab_select(&debut, first, word);
	ft_free_tab(table);
	free(var);
	free(word);
	return (0);
}
