/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_history.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/26 19:22:58 by dbaldy            #+#    #+#             */
/*   Updated: 2016/04/30 19:10:53 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		hist_err(char *com)
{
	ft_dprintf(STDERR_FILENO, "history: illegal argument: %s\n%s", com,
			"usage: history [number][-c][-hr][-number]\n");
	return (-2);
}

static int		other_opt(char *com, int *count)
{
	int		res;

	if (*count >= 0)
		return (0);
	res = 0;
	*count = 15;
	if (com[0] != '-')
		return (hist_err(com));
	if (ft_strchr(com, 'c') != NULL)
		res = -1;
	if (ft_strchr(com, 'h') != NULL)
		res = (res == 0) ? 1 : -2;
	if (ft_strchr(com, 'r') != NULL)
	{
		if (res == -1)
			return (hist_err(com));
		res += 2;
	}
	if (res == 0)
		return (hist_err(com));
	return (res);
}

static int		history_builtin_opt(char **com, int last_nb)
{
	if (com[1] && com[2])
	{
		ft_dprintf(STDERR_FILENO, "history: too many arguments\n");
		return (-1);
	}
	else if (com[1] == NULL)
		return (15);
	if (com[1][0] == '-' && ft_isdigit(com[1][1]))
		return (ft_atoi(&com[1][1]));
	else if (ft_isdigit(com[1][0]))
		return ((last_nb - ft_atoi(com[1]) >= 0) ? last_nb - ft_atoi(com[1]) :
				-1);
		return (-2);
}

static int		print_history(int opt, t_hist_list *buf, int flag)
{
	int				i;
	char			*str;
	t_hist_list		*tmp;

	i = -1;
	tmp = buf;
	ft_printf("flag:%d opt:%d\n", flag, opt);
	while (flag < 2 && buf->next && i++ < opt)
		buf = buf->next;
	while (buf)
	{
		str = line_list_retrieve(buf->old);
		if (flag & 1)
			ft_dprintf(STDOUT_FILENO, "%s\n", str);
		else
			ft_dprintf(STDOUT_FILENO, "%4d  %s\n", buf->nb, str);
		free(str);
		buf = (flag < 2) ? buf->previous : buf->next;
	}
	clear_hist(&tmp);
	return (0);
}

int				sh_builtin_history(char **com)
{
	int				count;
	t_hist_list		*buf;
	int				flag;

	if ((buf = retrieve_history(2, NULL)) == NULL)
		return (1);
	if ((count = history_builtin_opt(com, buf->nb - 1)) == -1)
	{
		clear_hist(&buf);
		return (1);
	}
	if ((flag = other_opt(com[1], &count)) >= 0)
		return (print_history(count, buf, flag));
	else if (flag == -1)
	{
		retrieve_history(3, NULL);
		clear_hist(&buf);
		return (0);
	}
	return (1);
}
