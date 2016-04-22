/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_modif_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 18:48:50 by dbaldy            #+#    #+#             */
/*   Updated: 2016/04/22 19:46:56 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"

static char		*full_glob(t_glob_list *match_list, char *path)
{
	char		*tmp;
	t_glob_list *list_buf;
	char		*insert;

	list_buf = match_list;
	while (list_buf)
	{
		tmp = ft_strdup(insert); 
		free(insert);
		insert = ft_strjoin_multiple(4, tmp, " ", path, list_buf->var);
		free(tmp);
		list_buf = list_buf->next;
	}
	return (insert);
}

int			glob_modif_str(char **str, t_glob_list *match_list, int i,
		char *path)
{
	int			size;
	char		*insert;
	char		*tmp;
	char		*to_replace;
	
	size = i;
	ft_printf("OK PASCAL\n");
	insert = ft_strdup("");
	while ((*str)[size] && (*str)[size] != ' ' && (*str)[size] != '/'
			&& (*str)[size] != '\n')
		size++;
	insert = full_glob(match_list, path);
	tmp = ft_strsub(*str, i, size);
	to_replace = ft_strjoin(path, tmp);
	free(tmp);
	free(path);
	ft_printf("%s\n", to_replace);
	*str = ft_replace_str(*str, to_replace, insert);
	free(insert);
	free(to_replace);
	return (0);
}
