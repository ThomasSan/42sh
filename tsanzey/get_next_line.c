/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/18 16:43:37 by tsanzey           #+#    #+#             */
/*   Updated: 2015/12/18 16:43:39 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"
#include "libft/libft.h"

int		get_next_line(int const fd, char **line)
{
	static char		*dst = NULL;
	int				i;

	if (fd < 0 || !line)
		return (-1);
	i = get_line_len(fd, &dst);
	if (i == -1)
		return (0);
	if (i == -2)
		return (-1);
	*line = ft_strsub(dst, 0, i);
	dst = del_line(dst, i + 1);
	return (1);
}

int		checknewline(char *s)
{
	int i;

	i = 0;
	if (s == NULL)
		return (-1);
	while (s[i] != '\n' && s[i] != '\0')
		i++;
	if (s[i] == '\n')
		return (i);
	else
		return (-1);
}

char	*del_line(char *s, int i)
{
	int		j;
	char	*tmp;

	tmp = (char *)malloc(sizeof(char *) * (ft_strlen(s) - i));
	j = 0;
	if (!tmp)
		return (NULL);
	while (s[i] != '\0')
	{
		tmp[j] = s[i];
		j++;
		i++;
	}
	tmp[j] = '\0';
	if (s)
		free(s);
	return (tmp);
}

int		get_line_len(int const fd, char **dst)
{
	int		i;
	int		ret;
	char	*tmp1;
	char	buf[BUFF_SIZE + 1];

	ret = 1;
	while (ret != 0 && ((i = checknewline(*dst)) == -1))
	{
		ret = read(fd, buf, BUFF_SIZE);
		if (ret == -1)
			return (-2);
		buf[ret] = '\0';
		tmp1 = *dst;
		if (*dst == NULL)
			*dst = ft_strdup(buf);
		else
			*dst = ft_strjoin(*dst, buf);
		free(tmp1);
	}
	if (ret == 0 && i == -1 && ft_strcmp("", *dst))
	{
		*dst = ft_strjoin(*dst, "\n");
		i = (ft_strlen(*dst) - 1);
	}
	return (i);
}
