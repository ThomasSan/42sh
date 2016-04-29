/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 18:39:58 by dbaldy            #+#    #+#             */
/*   Updated: 2016/04/29 18:51:22 by dbaldy           ###   ########.fr       */
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

int						replace_bang(char **str);
int						replace_dollars(char **str);
int						escape_quotes(char *str, int *i, int c);
char					**build_match_list(char *path, char *word, char *next);
int						match(char *tested, char *word);
t_glob_list				*add_elem_glob(char *match,
		t_glob_list *glob);
int						glob_recurs(char **to_analyze, int i);
int						clear_matchlist(t_glob_list *match_list);
int						glob_modif_str(char **str,
		t_glob_list *match_list, char *word, int *i);
int						ft_free_tab(char **table);
t_glob_list				*glob_progressiv(char *str);
int						strstr_cmd(char **str, int *i, t_hist_list **hist);
int						strcmp_cmd(char **str, int *i, t_hist_list **hist);
int						direct_digit(char **str, int *i, t_hist_list **hist);
int						backward_digit(char **str, int *i, t_hist_list **hist);
char					*remove_spec_car(char *to_glob);
#endif
