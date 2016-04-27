/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_backquotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 12:33:25 by tsanzey           #+#    #+#             */
/*   Updated: 2016/04/27 10:59:58 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "shell.h"
#include "ft_printf.h"

int		ft_sublen(char *str, int start, char c)
{
	int	i;

	i = 0;
	while (str[start + i++] && str[start + i] != c)
	{
	}
	return (i);
}

char	*ft_subcopy(char *str, int i)
{
	char	*tmp;
	int		j;
	int		len;

	len = ft_sublen(str, i, '`');
	j = 0;
	if (!(tmp = (char *)malloc(sizeof(char) * len)))
		return (NULL);
	len--;
	while (j < len)
	{
		tmp[j] = str[i + j + 1];
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

char	*ft_join_in_middle(char *src, char *dst, int i, int len)
{
	int		size;
	int		j;
	int		k;
	char	*ret;

	j = i + ft_strlen(dst);
	k = 1;
	size = ft_strlen(src) + ft_strlen(dst) - len;
	if (!(ret = (char *)malloc(sizeof(char) * size)))
		return (NULL);
	ft_bzero(ret, size);
	ret = ft_strncpy(ret, src, i);
	ret = ft_strcat(ret, dst);
	while (src[i + len + k])
	{
		ret[j] = src[i + len + k];
		j++;
		k++;
	}
	ret[j] = '\0';
	return (ret);
}

char	*ft_remove_bquotes(char *str, int i, int len)
{
	int		j;
	int		k;
	char	*tmp;

	j = 0;
	k = 0;
	if (!(tmp = (char *)malloc(sizeof(char) * ft_strlen(str) - len)))
		return (NULL);
	while (str[j + k])
	{
		if (j == i)
			k = len + 1;
		if (str[j + k] == '\0')
			break ;
		tmp[j] = str[j + k];
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

char	*ft_backquotes(char *str, int i)
{
	char	*dst;
	char	*tmp;
	t_tree	*root;
	int		len;

	dst = NULL;
	len = ft_sublen(str, i, '`');
	tmp = ft_subcopy(str, i);
	root = sh_lexer_parser(tmp);
	ft_bzero(tmp, ft_strlen(tmp));
	free(tmp);
	if (!(dst = exec_backquotes(root)))
		tmp = ft_remove_bquotes(str, i, len);
	else
		tmp = ft_join_in_middle(str, dst, i, len);
	// ft_printf("tmp %s\n", tmp);
	//free(str);
	free(dst);
	return (tmp);
}
