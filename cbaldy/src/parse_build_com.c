/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_build_com.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 17:33:25 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/14 13:08:13 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		parse_get_clog(char *s, int *clog)
{
	if (s[0] == '\0')
	{
		*clog = 0;
		return (0);
	}
	else if (s[0] == '|')
		*clog = 1;
	else if (s[0] == '<')
		*clog = 2;
	else
		*clog = 3;
	if (s[0] == s[1])
	{
		*clog += 2;
		return (2);
	}
	return (1);
}

static int		parse_create_exec_list(char *str, int clog, t_exec_list **begin)
{
	t_exec_list	*new;

	if ((new = exec_list_new(str, clog)) == NULL)
		return (0);
	exec_list_add(begin, new);
	return (0);
}

/*t_exec_list		*parse_in_out_check(t_exec_list *begin)
{
	t_exec_list	*tmp;
	int			i;

	tmp = begin;
	i = 0;
	if (tmp->clog == 3 || tmp ->clog == 5)
		i = -1;

}*/

t_exec_list		*parse_build_com(char *str)
{
	t_exec_list	*begin;
	char		*tmp;
	int			i[4];

	begin = NULL;
	if (parse_find_error(str) < 0)
		return (NULL);
	i[0] = 0;
	while (str[i[0]])
	{
		i[1] = 0;
		while (str[i[0] + i[1]] && str[i[0] + i[1]] != '<' && str[i[0] +
				i[1]] != '>' && str[i[0] + i[1]] != '|')
			i[1]++;
		tmp = ft_strsub(&(str[i[0]]), 0, i[1]);
		i[3] = parse_get_clog(&(str[i[0] + i[1]]), &i[2]);
		parse_create_exec_list(tmp, i[2], &begin);
		free(tmp);
		i[0] += i[1] + i[3];
	}
	return (begin);
	//return (parse_in_out_check(begin));
}
