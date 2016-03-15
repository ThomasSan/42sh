/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_find_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 12:22:09 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/10 11:38:56 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	parse_get_error_name(char *s)
{
	int		i;

	i = 1;
	while (s[i] != '\0' && s[i] == s[0])
		i++;
	if ((s[0] == '|' && i > 1) || ((s[0] == '>' || s[0] == '<') && i > 2))
		return (s[0]);
	while (s[i] && s[i] == ' ')
		i++;
	if (s[i] == '\0')
		return (s[0]);
	else if (s[i] == '|' || s[i] == '<' || s[i] == '>')
		return (s[i]);
	return (0);
}

static int	parse_is_valid(char *s)
{
	char	c;

	if ((c = parse_get_error_name(s)) != 0)
	{
		ft_dprintf(STDERR_FILENO, "shell: parse error near`%c'\n", c);
		return (-1);
	}
	if (s[0] == s[1])
		return (1);
	return (0);
}

int			parse_find_error(char *str)
{
	int		i[2];

	i[0] = 0;
	while (str[i[0]] && str[i[0]] == ' ')
		i[0]++;
	if (str[i[0]] == '<' || str[i[0]] == '>' || str[i[0]] == '|')
	{
		ft_dprintf(STDERR_FILENO, "shell: parse error near`%c'\n", str[i[0]]);
		return (-1);
	}
	while (str[i[0]] != 0)
	{
		if (str[i[0]] == '<' || str[i[0]] == '>' || str[i[0]] == '|')
		{
			if ((i[1] = parse_is_valid(&(str[i[0]]))) < 0)
				return (-1);
			i[0] += i[1];
		}
		i[0]++;
	}
	return (0);
}
