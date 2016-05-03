/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_finish_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 18:32:23 by cbaldy            #+#    #+#             */
/*   Updated: 2016/05/02 18:01:14 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	*finish_line_init_tab(void)
{
	int		*arr;

	if ((arr = (int *)malloc(sizeof(int) * 7)) == NULL)
		return (NULL);
	arr[0] = 0;
	arr[1] = 0;
	arr[2] = 0;
	arr[3] = 0;
	arr[4] = 0;
	arr[5] = 0;
	arr[6] = 0;
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

static int	term_backslach(char *str, int *arr)
{
	if (str[1] == '\0')
	{
		arr[6] = 1;
		return (1);
	}
	else if (str[1] == '(' || str[1] == ')' || str[1] == '[' || str[1] == ']'
			|| str[1] == '{' || str[1] == '}' || str[1] == 39 || str[1]
			== '"' || str[1] == '`' || str[1] == 92 || str[1] == 10)
		return (2);
	return (1);
}

static int	term_read_string(char *str, int *arr)
{
	int		i;

	i = 1;
	if (str[0] == 92)
		return (term_backslach(str, arr));
	lex_is_special(str[0], arr);
	if ((str[0] == '`' && arr[5] != 0) || (str[0] == 34 &&
				arr[4] != 0) || (str[0] == 39 && arr[3] != 0))
	{
		while (str[i] && str[i] != str[0])
		{
			if (str[0] == '"' && str[i] == 92)
				i++;
			i++;
		}
	}
	return (i);
}

int			term_finish_line(t_line_list *first)
{
	char	*str;
	int		*arr;
	int		i[2];

	while (first->previous != NULL)
		first = first->previous;
	str = line_list_retrieve(first);
	arr = finish_line_init_tab();
	i[0] = 0;
	while (str[i[0]] != '\0')
		i[0] += term_read_string(&(str[i[0]]), arr);
	free(str);
	i[0] = 0;
	i[1] = 0;
	while (i[0] < 7)
	{
		if (arr[i[0]] > 0)
			i[1] = -1;
		i[0]++;
	}
	free(arr);
	return (i[1]);
}
