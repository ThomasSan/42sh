/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 18:39:58 by dbaldy            #+#    #+#             */
/*   Updated: 2016/04/22 17:37:37 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOB_H
# define GLOB_H

# include "shell.h"

typedef struct			s_glob_list
{
	char				*var;
	struct s_glob_list	*next;
	struct s_glob_list	*prev;
}						t_glob_list;

int						escape_quotes(char *str, int *i, int c);
int						glob_new_string(char **str);
t_glob_list				*build_match_list(char **path, char *word);
int						match(char *tested, char *word);
t_glob_list				*add_elem_glob(char *path, char *match,
		t_glob_list *glob);
int						clear_matchlist(t_glob_list *match_list);
int						glob_modif_str(char **str,
		t_glob_list *match_list, int i);
int						ft_free_tab(char **table);
#endif
