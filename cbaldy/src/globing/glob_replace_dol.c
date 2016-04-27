/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_replace_dol.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 12:59:08 by dbaldy            #+#    #+#             */
/*   Updated: 2016/04/27 17:50:07 by dbaldy           ###   ########.fr       */
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

static int		escape_questm(int *i)
{
	*i += 2;
	return (0);
}

static int		replace_dollar(char **str, int *i)
{
	int			j;
	char		*value;
	char		*var;
	char		*tmp;

	j = *i;
	if ((*str)[*i + 1] == '?')
		return (escape_questm(i));
	while ((*str)[j + 1] && (*str)[j + 1] != ' ' && (*str)[j + 1] != '\n'
			&& (*str)[j + 1] != '/')
		j++;
	var = ft_strsub(*str, *i + 1, j - *i);
	value = get_replacement(var);
	tmp = var;
	var = ft_strjoin("$", tmp);
	free(tmp);
	tmp = ft_replace_str(*str, var, value);
	free(*str);
	*str = tmp;
	*i = (ft_strlen(value) == 0) ? *i + 1 : ft_strlen(value);
	free(var);
	free(value);
	return (0);
}

int				replace_dollars(char **str)
{
	int		i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == ' ' && (*str)[i + 1] == '~')
			alias_ihome(str, i + 1);
		if ((*str)[i] == 0x22 || (*str)[i] == 0x27)
			escape_quotes(*str, &i, (*str)[i]);
		else if ((*str)[i] == '$')
			replace_dollar(str, &i);
		else if ((*str)[i] != '\0')
			i = ((*str)[i] == 0x5c) ? i + 2 : i + 1;
	}
	return (0);
}
