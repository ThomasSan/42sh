/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 14:07:35 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/15 11:45:48 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static t_param	*add_file(t_param *debut, char *str)
{
	t_param		*buf;
	t_param		*new;

	buf = debut;
	while (buf->next)
		buf = buf->next;
	if ((new = (t_param*)malloc(sizeof(t_param))) == NULL)
		return (NULL);
	new->var = ft_strdup(str);
	new->next = NULL;
	new->prev = buf;
	buf->next = new;
	new->nb = buf->nb + 1;
	new->select = 0;
	return (new);
}

t_param			*list_param(char **argv)
{
	int			i;
	t_param		*debut;
	t_param		*new;

	i = 2;
	new = NULL;
	if (argv == NULL || argv[1] == NULL)
		return (NULL);
	if ((debut = (t_param*)malloc(sizeof(t_param))) == NULL)
		return (NULL);
	debut->var = ft_strdup(argv[1]);
	debut->nb = 0;
	debut->select = 1;
	debut->prev = NULL;
	debut->next = NULL;
	while (argv[i])
	{
		new = add_file(debut, argv[i]);
		i++;
	}
	if (new != NULL)
		new->next = debut;
	debut->prev = (new != NULL) ? new : debut;
	debut->next = (new != NULL) ? debut->next : debut;
	return (debut);
}

int				init_term(void)
{
	struct termios	term;

	tcgetattr(get_fd(0), &term);
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(get_fd(0), TCSADRAIN, &term);
	return (0);
}
