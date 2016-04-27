/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 17:53:12 by dbaldy            #+#    #+#             */
/*   Updated: 2016/04/26 19:35:27 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	move i to next quote of same type c in str
**	if quote found, return 0 and sets i to next element in str
**	else return 1
*/
#include <stdio.h>
#include <stdlib.h>
int			escape_quotes(char *str, int *i, int c)
{
	int var;

	var = *i + 1;
	while (str[var])
	{
		if ((int)str[var] == 0x5c && c != 0x27 && str[var + 1] != '\0')
			var += 2;
		else if ((int)str[var] == c)
		{
			*i = var + 1;
			return (0);
		}
		else
			var++;
	}
	return (1);
}
