/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 10:53:07 by nchrupal          #+#    #+#             */
/*   Updated: 2016/04/25 16:43:02 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHTABLE_H
# define HASHTABLE_H

# define BUFF_SZ 1024
# define SZHASH 97

typedef struct		s_hash
{
	unsigned		key;
	char			cmd[BUFF_SZ + 1];
	char			fullpath[BUFF_SZ + 1];
	struct s_hash	*next;
}					t_hash;

void				*xmalloc(size_t size);
t_hash				*hash_new(void);
void				hash_del(void);
unsigned			hash_key(char *cmd);
t_hash				*hash_createfile(void);
void				hash_addfile(char *path);
t_hash				*hash_exist(char *cmd);
t_hash				*hash_insert(char *cmd, char *fullpath);

#endif
