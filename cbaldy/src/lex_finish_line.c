/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_finish_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/05 19:12:16 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/08 11:05:58 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*lex_finish_line_join(t_com_list *begin)
{
	char	*str[3];

	str[0] = "";
	str[1] = "";
	if (g_local->begin != NULL)
		str[0] = com_list_retrieve(g_local->begin);
	if (begin != NULL)
		str[1] = com_list_retrieve(begin);
	str[2] = ft_strjoin(str[0], str[1]);
	if (str[0][0] != '\0')
		free(str[0]);
	if (str[1][0] != '\0')
		free(str[1]);
	return (str[2]);
}

static int	*finish_line_init_tab(void)
{
	int		*arr;

	if ((arr = (int *)malloc(sizeof(int) * 6)) == NULL)
		return (NULL);
	arr[0] = 0;
	arr[1] = 0;
	arr[2] = 0;
	arr[3] = 0;
	arr[4] = 0;
	arr[5] = 0;
	return (arr);
}

static int	lex_is_special(char c, int *arr)
{
	if (c == '(')
		arr[0] += 1;
	else if (c == ')')
		arr[0] -= 1;
	else if (c == '{')
		arr[1] += 1;
	else if (c == '}')
		arr[1] -= 1;
	else if (c == '[')
		arr[2] += 1;
	else if (c == ']')
		arr[2] -= 1;
	else if (c == '\'')
		arr[3] ^= 1;
	else if (c == '"')
		arr[4] ^= 1;
	else if (c == '`')
		arr[5] ^= 1;
	return (0);
}

static int	lex_return_value(int *arr)
{
	int		i[2];
	
	i[0] = 0;
	i[1] = 0;
	while (i[0] < 6)
	{
		if (arr[i[0]] > 0)
			i[1] = -1;
		i[0]++;
	}
	return (i[1]);
}

int			lex_finish_line(t_com_list *begin)
{
	char	*str;
	int		*arr;
	int		i[2];

	str = lex_finish_line_join(begin);
	arr = finish_line_init_tab();
	i[0] = 0;
	while (str[i[0]] != '\0')
	{
		lex_is_special(str[i[0]], arr);
		if ((str[i[0]] == '`' && arr[5] != 0) || (str[i[0]] == '"' &&
					arr[4] != 0) || (str[i[0]] == '\'' && arr[3] != 0))
		{
			i[1] = i[0];
			while (str[i[1] + 1] && str[i[1] + 1] != str[i[0]])
				i[1]++;
			i[0] = i[1];
		}
		i[0]++;
	}
	free(str);
	i[0] = lex_return_value(arr);
	free(arr);
	return (i[0]);
}
