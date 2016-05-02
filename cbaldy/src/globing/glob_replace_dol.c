/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_replace_dol.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 12:59:08 by dbaldy            #+#    #+#             */
/*   Updated: 2016/05/02 12:44:21 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"

static char		*get_replacement(char *var)
{
	char	*res;
	int		i;

	i = 0;
	while (var[i])
	{
		var[i] = ft_toupper(var[i]);
		i++;
	}
	if ((i = sh_is_new_var(var)) >= 0)
		res = ft_strdup(ft_strchr(g_env[i], '=') + 1);
	else
		res = ft_strdup("");
	return (res);
}

static int		up_var(char *str, int start, int length)
{
	int		j;

	j = start;
	while (str[j] && j < length + start)
	{
		str[j] = ft_toupper(str[j]);
		j++;
	}
	return (0);
}

static char		*get_replaced(char *str, int *i, int j)
{
	char		*var;
	char		*value;
	char		*tmp;
	char		*res;

	var = ft_strsub(str, j + 1, *i - j);
	value = get_replacement(var);
	tmp = var;
	var = ft_strjoin("$", tmp);
	up_var(str, j + 1, *i - j);
	res = ft_replace_str(str, var, value);
	*i = (ft_strlen(value) == 0) ? j + 1 : j + ft_strlen(value) - 1;
	free(tmp);
	free(var);
	free(value);
	return (res);
}

static int		replace_dollar(char **str, int *i)
{
	int			j;
	char		*tmp;

	j = *i;
	if ((*str)[*i + 1] == '?' || (ft_isalnum((*str)[*i + 1]) == 0 &&
				(*str)[*i + 1] != '_'))
	{
		*i += 2;
		return (0);
	}
	while ((*str)[*i + 1] && (ft_isalnum((*str)[*i + 1]) == 1 ||
		(*str)[*i + 1] == '_') && *i - j < 256)
		(*i)++;
	tmp = get_replaced(*str, i, j);
	free(*str);
	*str = tmp;
	return (0);
}

int				replace_dollars(char **str)
{
	int		i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == 0x27)
			escape_quotes(*str, &i, (*str)[i]);
		else if ((*str)[i] == '$')
			replace_dollar(str, &i);
		else if ((*str)[i] != '\0')
			i = ((*str)[i] == 0x5c) ? i + 2 : i + 1;
	}
	return (0);
}
