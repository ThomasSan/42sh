/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_number_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 12:45:47 by dbaldy            #+#    #+#             */
/*   Updated: 2016/04/28 12:51:38 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_number_size(char *str)
{
	int		count;

	count = 0;
	while (str[count] && ft_isdigit(str[count]) == 1)
		count++;
	return (count);
}
