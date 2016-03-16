/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 14:38:45 by dbaldy            #+#    #+#             */
/*   Updated: 2016/02/17 11:20:14 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = ft_strlen(s) - 1;
	if (j == 0 && s[0] != ' ' && s[0] != '\n' && s[0] != '\t')
		return (ft_strdup(s));
	while ((s[i] == ' ') || (s[i] == '\n') || (s[i] == '\t'))
		i++;
	while (((s[j] == ' ') || (s[j] == '\n') || (s[j] == '\t')) && j > 0)
		j--;
	if (j <= i)
		return (ft_strnew(1));
	if ((str = ft_strsub(s, i, j - i + 1)) == NULL)
		return (NULL);
	return (str);
}
