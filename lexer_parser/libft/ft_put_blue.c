/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_blue.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <tsanzey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 13:57:36 by tsanzey           #+#    #+#             */
/*   Updated: 2016/02/10 13:57:37 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_blue(char *s, int fd)
{
	ft_putstr_fd("\033[1;36m", fd);
	ft_putendl_fd(s, fd);
	ft_putstr_fd("\033[0m", fd);
}

void	ft_putstr_blue(char *s, int fd)
{
	ft_putstr_fd("\033[1;36m", fd);
	ft_putstr_fd(s, fd);
	ft_putstr_fd("\033[0m", fd);
}
