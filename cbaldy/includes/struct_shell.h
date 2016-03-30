/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_shell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/25 12:18:39 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/30 21:00:26 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_SHELL_H
# define STRUCT_SHELL_H

# include "tree_build_cmd.h"

typedef struct			s_edit_line
{
	char				*id;
	int					ret;
}						t_edit_line;

typedef struct			s_builtin
{
	char				*name;
	int					(*f)(char **com);
}						t_builtin;

typedef struct			s_com_list
{
	char				c;
	unsigned char		op;
	struct s_com_list	*next;
	struct s_com_list	*previous;
}						t_com_list;

typedef struct			s_line_list
{
	struct s_com_list	*begin;
	int					marge;
	struct s_line_list	*next;
	struct s_line_list	*previous;
}						t_line_list;

typedef struct			s_local
{
	int					completion;
	int					prompt;
	int					curs;
	int					nb_col;
	int					le_mode;
	t_com_list			*begin;
}						t_local;

typedef struct			s_hist_list
{
	int					nb;
	struct s_com_list	*old;
	struct s_hist_list	*next;
	struct s_hist_list	*previous;
}						t_hist_list;

typedef struct			s_exec_list
{
	int					id;
	int					(*f)(t_tree *root);
}						t_exec_list;

char					**g_env;
struct s_local			*g_local;
char					*g_paste;
int						g_std_fd[3];

#endif
