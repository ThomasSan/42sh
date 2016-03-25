/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_prepare_select.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 15:38:55 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/25 15:35:47 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	delete_word_compl(char *prev_var, t_com_list *begin)
{
	int		gap;

	gap = ft_strlen(prev_var) - ft_strlen(g_curr_compl->var);
	while (gap--)
		term_write_line(&begin, 127);
	return (0);
}

char		*tab_prepare_select(t_param *debut, t_com_list *begin)
{
	t_param		*buf;
	char		*test;

	buf = debut;
	if (buf->select == 2)
	{
		test = ft_strsub(debut->var, ft_strlen(g_curr_compl->var),
				ft_strlen(debut->var) - ft_strlen(g_curr_compl->var));
		buf->select = 1;
	}
	else
	{
		while (buf->prev->select == 0)
			buf = buf->next;
		test = ft_strsub(buf->var, ft_strlen(g_curr_compl->var),
				ft_strlen(buf->var) - ft_strlen(g_curr_compl->var));
		buf->prev->select = 0;
		buf->select = 1;
		delete_word_compl(buf->prev->var, begin);
	}
	return (test);
}

char		*file_suffix(char *str, char *path)
{
	struct stat		*buf;
	char			*aux;
	char			*tmp;

	aux = ft_strjoin(path, str);
	if ((buf = (struct stat*)malloc(sizeof(struct stat))) == NULL)
		return (ft_strdup(str));
	if (lstat(aux, buf) == -1)
		tmp = ft_strdup(str);
	else if (buf->st_mode & S_IFDIR)
		tmp = ft_strjoin(str, "/");
	else
		tmp = ft_strdup(str);
	free(buf);
	free(aux);
	return (tmp);
}
