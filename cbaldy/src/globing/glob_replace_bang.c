/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_replace_bang.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 17:16:36 by dbaldy            #+#    #+#             */
/*   Updated: 2016/04/27 19:16:59 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"

static int	rcpy_begin_line(char **str, int *i)
{
	char	*begin;
	
	begin = ft_strsub(*str, 0, *i);
	tmp = ft_ireplace_str(*str, begin, *i, 2);
	*i += ft_strlen(begin);
	return (0);
}

static int	to_nhist(char **str, int *i, t_hist_list **hist, int h_nb)
{
	t_hist_list		*buf;
	char			*to_add;

	buf = *hist;
	while (buf)
	{
		if ((*hist)->nb == h_nb)
		{
			to_add = line_list_retrieve((*hist)->old);
		}
	}
}

static int	replace_bangs(char **str, int *i)
{
	t_hist_list	*hist;

	if ((*str)[i + 1] == '#')
		return (rcpy_begin_line(str, i));
	if ((hist = retrieve_history(2, NULL)) == NULL)
		return (-1);
	if (ft_isdigit((*str)[i + 1]) == 1)
		return (to_nhist(str, i, &hist, ft_atoi(&((*str)[i + 1]))));
	else if ((*str)[i + 1] == '-')
	{
		if (ft_isdigit((*str)[i + 2]) == 1)
			return (to_nhist(str, i, &hist, 1 + hist->nb -
					ft_atoi(&((*str)[i + 1]))));
		else
			return (-2);
	}
	else if ((*str)[i + 1] == '!')
		return (to_nhist(str, i, &hist, hist->nb));
	else if ((*str)[i + 1] == '?')
		return (strstr_cmd(str, i, &hist));
	return (0);
}

int			replace_bang(char **str)
{
	int		i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == ' ' && (*str)[i + 1] == '~')
			alias_ihome(str, i + 1);
		else if ((*str)[i] == 0x22 || (*str)[i] == 0x27)
			escape_quotes(*str, &i, (*str)[i]);
		else if ((*str)[i] == '!')
		{
			if (replace_bangs(str, &i) < 0)
			{
				free(*str);
				*str = ft_strdup("");
				return (-1);
			}
		}
		else if ((*str)[i] != '\0')
			i = ((*str)[i] == 0x5c) ? i + 2 : i + 1;
	}
	ft_printf("%s\n", *str);
	exit(0);
	return (0);
}
