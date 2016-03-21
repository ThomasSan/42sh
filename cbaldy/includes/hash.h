/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 10:56:52 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/21 13:05:15 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_H
# define HASH_H

typedef struct			s_hash_tree
{
	char				*name;
	char				*path;
	struct s_hash_tree	*left;
	struct s_hash_tree	*right;
	struct s_hash_tree	*root;
}						t_hash_tree;

char					**g_hash;

int						hash_get_tab(void);
int						hash_build_tree(char *name, char *path,
		t_hash_tree **root);

#endif
