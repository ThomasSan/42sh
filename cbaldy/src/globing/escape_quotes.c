/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 17:53:12 by dbaldy            #+#    #+#             */
/*   Updated: 2016/04/25 14:29:37 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	move i to next quote of same type c in str
**	if quote found, return 0 and sets i to next element in str
**	else return 1
*/
#include <stdio.h>
int			escape_quotes(char *str, int *i, int c)
{
	int var;

	var = *i + 1;
	while (str[var])
	{
		if ((int)str[var] == 0x5c && c != 0x27 && str[var + 1] != '\0')
				var += 2;
		if ((int)str[var] == c)
		{
			*i = var + 1;
			return (0);
		}
		var++;
	}
	return (1);
}
