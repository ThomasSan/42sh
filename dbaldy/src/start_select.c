/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/17 17:00:44 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/15 11:50:25 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int		print_result(t_param *debut)
{
	t_param	*param;
	int		count;

	param = debut;
	count = 0;
	while (42)
	{
		if ((param->select / 2) == 1)
		{
			if (count > 0)
				ft_dprintf(STDOUT_FILENO, " ");
			count++;
			ft_dprintf(STDOUT_FILENO, "%s", param->var);
		}
		if (param->next->nb == 0)
			break ;
		param = param->next;
	}
	if (count > 0)
		ft_dprintf(STDOUT_FILENO, "\n");
	return (0);
}

int				boucle(char **arg)
{
	t_param			*debut;
	int				ret;

	if (arg == NULL)
		return (-1);
	else if ((debut = list_param(arg)) == NULL)
		return (-1);
	g_debut = debut;
	while ((ret = ft_select(&debut)) == 0)
		;
	reset_term();
	if (ret > 0)
		print_result(debut);
	clear_list(&debut);
	return (ret);
}

int				start_select(int ac, char **arg)
{
	if (ac < 2)
		return (-1);
	signal(SIGTSTP, sig_handler);
	signal(SIGCONT, sig_handler);
	signal(SIGWINCH, sig_handler);
	signal(SIGINT, sig_handler);
	signal(SIGTERM, sig_handler);
	if (boucle(arg) == -1)
		return (-1);
	return (0);
}
