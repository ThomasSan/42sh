/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_supp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 15:14:39 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/23 12:53:44 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_param		*add_file(t_param *debut, char *str)
{
	t_param		*buf;
	t_param		*new;

	buf = debut;
	while (buf && buf->next)
		buf = buf->next;
	if ((new = (t_param*)malloc(sizeof(t_param))) == NULL)
		return (NULL);
	new->var = ft_strdup(str);
	new->next = NULL;
	new->prev = buf;
	if (buf != NULL)
	{
		buf->next = new;
		new->nb = buf->nb + 1;
	}
	else
		new->nb = 0;
	new->select = (buf == NULL) ? 1 : 0;
	return (new);
}

static char	*ft_strtrim2(char *s)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(s) - 1;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	while ((s[j] == ' ' || s[j] == '\n' || s[j] == '\t') && j > 0)
		j--;
	if (i > j)
		return (NULL);
	return (ft_strsub(s, i, j - i + 1));
}

char		*com_list_string(t_com_list *begin)
{
	int			size;
	char		*buf;
	char		*new;

	buf = com_list_retrieve(begin);
	size = g_local->curs - g_local->prompt - 2;
	while (buf[size] && buf[size] != ' ')
		size++;
	new = (size <= 0) ? NULL : ft_strsub(buf, 0, size);
	free(buf);
	return (ft_strtrim2(new));
}

int			iscommand(char *var)
{
	while (*var)
	{
		if (*var == ' ')
			return (1);
		var++;
	}
	return (0);
}

int			fputchar(int c)
{
	ft_putchar_fd(c, STDIN_FILENO);
	return (0);
}
