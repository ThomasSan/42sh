/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 19:20:04 by cbaldy            #+#    #+#             */
/*   Updated: 2015/11/30 10:45:54 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_sqrt(int nb)
{
	int	i;
	int j;

	if (nb < 0)
		return (0);
	else
	{
		j = 0;
		i = 0;
		while (i < 47000)
		{
			if (i * i == nb)
			{
				j = i;
				i = 47000;
			}
			i++;
		}
		return (j);
	}
}