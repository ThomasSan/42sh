/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 18:06:52 by cbaldy            #+#    #+#             */
/*   Updated: 2015/11/30 18:59:38 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_digit(int n)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	if (n == -2147483648)
		return (10);
	if (n < 0)
		n = -n;
	while (n / i > 0 && j < 10)
	{
		j++;
		i = i * 10;
	}
	if (j == 10)
		return (10);
	if (n == 0)
		return (1);
	else
		return (j);
}

char			*ft_itoa(int n)
{
	int		i;
	int		moins;
	char	*str;

	moins = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		n = -n;
		moins++;
	}
	if ((str = ft_strnew(ft_digit(n) + moins)) == NULL)
		return (NULL);
	if (moins > 0)
		str[0] = '-';
	i = ft_digit(n) + moins - 1;
	while (i >= moins)
	{
		str[i] = 48 + (n % 10);
		i--;
		n = n / 10;
	}
	return (str);
}
