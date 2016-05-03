/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_finish_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 15:53:44 by cbaldy            #+#    #+#             */
/*   Updated: 2016/05/03 12:08:01 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	*finish_line_init_tab_mini(void)
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

static int	lex_is_special_mini(char c, int *arr)
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

static int	mini_backslach(char *str, int *arr)
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

static int	mini_read_string(char *str, int *arr)
{
	int		i;

	i = 1;
	if (str[0] == 92)
		return (mini_backslach(str, arr));
	lex_is_special_mini(str[0], arr);
	if ((str[0] == '`' && arr[5] != 0) || (str[0] == 34 &&
				arr[4] != 0) || (str[0] == 39 && arr[3] != 0))
	{
		while (str[i] && str[i] != str[0])
		{
			if ((str[0] == '"' || str[0] == '`') && str[i] == 92)
				i++;
			i++;
		}
	}
	return (i);
}

int			mini_finish_line(char *str)
{
	int		*arr;
	int		i[2];

	arr = finish_line_init_tab_mini();
	i[0] = 0;
	while (str[i[0]] != '\0')
		i[0] += mini_read_string(&(str[i[0]]), arr);
	i[0] = 0;
	i[1] = 0;
	while (i[0] < 7)
	{
		if (arr[i[0]] != 0)
			i[1] = -1;
		i[0]++;
	}
	free(arr);
	if (i[1] < 0)
		ft_dprintf(STDERR_FILENO, "shell: bad pattern\n");
	return (i[1]);
}
