/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/29 17:21:29 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/15 10:21:27 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H
# include "minishell.h"
# include "ft_select.h"
# include "libft.h"
# include "ft_printf.h"
# define HIST_SIZE 5

typedef struct				s_command_line
{
	char					c;
	int						select;
	int						nb;
	struct s_command_line	*next;
	struct s_command_line	*prev;
}							t_line;

typedef struct				s_historique
{
	int						nb;
	t_line					*begin;
	struct s_historique		*next;
	struct s_historique		*prev;
}							t_hist;

t_hist						*copy_hist(t_hist *historique,
		t_line *current_line);
int							select_end(t_line *current_line);
int							suppr_char_list(t_line **chaine);
int							go_end(t_line *current_line);
int							go_home(t_line *current_line);
int							return_to_prompt(t_line *current_line);
int							move_cursor(char direction, t_line *buf);
int							line_to_print(t_line *elem);
int							update_list(t_hist **historique,
		t_line *current_line);
int							print_line(t_line *debut);
int							change_hist(char direction, t_hist **historique,
		t_line **current_line);
int							clear_tline(t_line **elem);
int							clear_thist(t_hist **debut);
int							retrieve_char(t_line *historique);
t_line						*copy_tline(t_line *begin);
int							line_of_command(t_line *debut, char **str);
int							get_line_of_command(int fd, char **str);
int							map_key(char *buf, t_hist **historique,
		t_line **current_line);
#endif
