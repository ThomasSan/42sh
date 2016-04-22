/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_modif_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 18:48:50 by dbaldy            #+#    #+#             */
/*   Updated: 2016/04/22 18:46:07 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"

int			glob_modif_str(char **str, t_glob_list *match_list, int i)
{
	int			size;
	char		*insert;
	char		*tmp;
	t_glob_list	*list_buf;

	list_buf = match_list;
	size = i;
	insert = ft_strdup("");
	while ((*str)[size] && (*str)[size] != ' ' && (*str)[size] != '/'
			&& (*str)[size] != '\n')
		size++;
	while (match_list)
	{
		tmp = ft_strdup(insert); 
		free(insert);
		insert = ft_strjoin_multiple(3, tmp, " ", match_list->var);
		free(tmp);
		match_list = match_list->next;
	}
	tmp = ft_strsub(*str, i, size);
	*str = ft_replace_str(*str, tmp, insert);
	free(insert);
	match_list = list_buf;
	return (0);
}
