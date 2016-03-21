/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_mode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 13:40:47 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/21 19:09:35 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_select.h"

static t_param		*string_matches(char *var, char **buf)
{
	size_t		size;
	int			i;
	t_param		*debut;

	size = ft_strlen(var);
	i = 0;
	while (buf[i])
	{
		if (ft_strncmp(var, buf[i], size) == 0)
			debut = add_file(debut, buf[i]);
		i++;
	}
	return (debut);
}

static char			**tabl_compl(int size, char *path)
{
	DIR				*dip;
	struct dirent	*lol;
	char			**res;
	int				i;

	if (size == 0)
		return (NULL);
	if ((res = (char**)malloc(sizeof(char*) * (size + 1))) == NULL)
		return (NULL);
	if ((dip = opendir(path)) == NULL)
	{
		free(res);
		return (NULL);
	}
	i = 0;
	while ((lol = readdir(dip)))
	{
		res[i] = ft_strdup(lol->d_name);
		i++;
	}
	closedir(dip);
	free(path);
	return (res);
}

static char			**list_path(char *var)
{
	char			*buf;
	DIR				*dip;	
	struct dirent	*lol;
	int				count;

	count = 0;
	buf = ft_strrchr(var, ' ');
	buf = (ft_strchr(buf, '/') == NULL) ? ft_strdup(".") :
		ft_strtrunc(buf, '/');
	if ((dip = opendir(buf)) == NULL)
		return (NULL);
	while ((lol = readdir(dip)))
		count++;
	closedir(dip);
	return (tabl_compl(count, buf));
}

static int			iscommand(char *var)
{
	while (*var)
	{
		if (*var == ' ')
			return (0);
		var++;
	}
	return (1);
}

int					tab_mode(t_com_list *begin)
{
	t_param				*debut;
	char				*var;
	char				**table;

	if (begin == NULL)
		return (0);
	if ((var = com_list_string(begin)) == NULL)
		return (-1);
	table = (iscommand(var) == 0) ? g_hash : list_path(var);
	if (table == NULL)
		return (0);
	debut = string_matches(var, table);
	if (debut != NULL)
		tab_select(debut, begin);
	if (iscommand(var) != 0)
		ft_free_tab(table);
	free(var);
	return (0);
}
