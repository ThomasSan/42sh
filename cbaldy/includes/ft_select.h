/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/17 17:00:59 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/22 13:54:55 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <termios.h>
# include <term.h>
# include <fcntl.h>
# include <curses.h>
# include <sys/ioctl.h>
# include "libft.h"
# include "ft_printf.h"
# include <sys/stat.h>
# include "shell.h"

typedef struct				s_command_line
{
	char					c;
	int						select;
	int						nb;
	struct s_command_line	*next;
	struct s_command_line	*prev;
}							t_line;

typedef struct				s_arg_list
{
	char					*var;
	int						nb;
	int						select;
	struct s_arg_list		*next;
	struct s_arg_list		*prev;
}							t_param;

int							iscommand(char *var);
t_param						*add_file(t_param *debut, char *str);
int							reset_select(t_param *debut);
int							suppr_char_list(t_line **line);
int							increase_nb(t_line *elem);
int							clear_tline(t_line **elem);
int							multi_select(t_param *debut, t_line *line);
int							manage_hist(char *buf, t_param *debut, int nb_row,
		int check);
int							print_line(t_line *str);
int							change_select(t_param *debut, t_line *line);
int							open_history(int nb_row, int check, t_param *debut);
int							get_height(void);
int							get_width(void);
int							get_size_list(t_param *debut);
int							get_nb_col(t_param *debut);
int							get_nb_tab(t_param *debut);
int							get_nb_row(t_param *debut, int nb_col);
int							init_term(void);
int							boucle(char **arg);
void						sig_handler(int sig);
void						clear_list(t_param **debut);
int							get_fd(int type);
void						reset_term(void);
int							read_key(char *buf, t_param **debut);
void						go_to_origin(int row);
int							print_lines(int nb_row);
int							move_cursor_one_down(int size, int col_nb);
int							ft_notputs(char *str, int occ);
int							move_cursor_up(int nb_row, int nb_tab);
int							tab_select(t_param *debut, t_com_list *begin);
char						*com_list_string(t_com_list *begin);
t_param						*list_param(char **argv);
int							fputchar(int c);
t_param						*g_debut;

#endif
