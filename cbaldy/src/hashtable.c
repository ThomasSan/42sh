/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 08:53:14 by nchrupal          #+#    #+#             */
/*   Updated: 2016/04/25 16:43:00 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "hashtable.h"
#include "shell.h"

t_hash	*g_hashtable = NULL;

void	*xmalloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
	{
		ft_putendl_fd("error: malloc failed", 2);
		exit(1);
	}
	return (ptr);
}

t_hash		*hash_new(void)
{
	if (g_hashtable == NULL)
	{
		g_hashtable = xmalloc(SZHASH * sizeof(*g_hashtable));
		ft_bzero(g_hashtable, SZHASH * sizeof(*g_hashtable));
	}
	return (g_hashtable);
}

void		hash_del(void)
{
	t_hash	*tmp;
	int		i;

	if (g_hashtable == NULL)
		return ;
	i = 0;
	while (i < SZHASH)
	{
		while (g_hashtable[i].next != NULL)
		{
			tmp = g_hashtable[i].next->next;
			free(g_hashtable[i].next);
			g_hashtable[i].next = tmp;
		}
		i++;
	}
	free(g_hashtable);
	g_hashtable = NULL;
}

unsigned	hash_key(char *cmd)
{
	unsigned	key;

	key = 0;
	while (*cmd)
	{
		key = key * SZHASH + *cmd;
		cmd++;
	}
	return (key % SZHASH);
}

t_hash		*hash_exist(char *cmd)
{
	unsigned	key;
	t_hash		*tmp;

	key = hash_key(cmd);
	tmp = g_hashtable + key;
	while (tmp != NULL && ft_strcmp(tmp->cmd, cmd) != 0)
		tmp = tmp->next;
	return (tmp);
}
