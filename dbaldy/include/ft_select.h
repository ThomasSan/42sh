/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/17 17:00:59 by dbaldy            #+#    #+#             */
/*   Updated: 2016/02/29 17:28:51 by dbaldy           ###   ########.fr       */
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

typedef struct			s_arg_list
{
	char				*var;
	int					nb;
	int					select;
	struct s_arg_list	*next;
	struct s_arg_list	*prev;
}						t_param;

typedef struct			s_list_data
{
	int					height;
	int					width;
	int					size_list;
	int					size_max;
	int					nb_tab;
	int					nb_col;
	int					nb_row;
}						t_data;

int						get_height(void);
int						get_width(void);
int						get_size_list(t_param *debut);
int						get_nb_col(t_param *debut);
int						get_nb_tab(t_param *debut);
int						get_nb_row(t_param *debut, int nb_col);
int						init_term(void);
int						mesure_size_max(t_param *debut, t_data *donnees);
int						boucle(char **arg);
void					sig_handler(int sig);
void					clear_list(t_param **debut);
int						get_fd(int type);
void					reset_term(void);
int						ft_tputs(char *mvt, int nb_occ);
int						read_key(char *buf, t_param **debut);
void					go_to_origin(int row);
int						print_lines(int nb_row);
int						move_cursor_one_down(int size, int col_nb);
int						move_cursor_up(int nb_row, int nb_tab);
int						ft_select(t_param **debut);
t_param					*list_param(char **argv);
int						fputchar(int c);
t_param					*g_debut;
int						print_args(t_param *debut);
#endif
