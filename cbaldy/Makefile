# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/14 14:42:25 by cbaldy            #+#    #+#              #
#    Updated: 2016/03/21 17:04:43 by cbaldy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

SRC = main.c sh_set_term.c sh_read_prompt.c sh_command.c sh_builtin_cd.c \
	  sh_builtin_env.c ft_1_aux.c sh_builtin_exit.c cd_exist_error.c \
	  sh_builtin_setenv.c sh_add_var_env.c sh_builtin_unsetenv.c \
	  cd_get_path.c sh_set_env.c env_custom.c cd_substitution.c \
	  sh_interpret_com.c ft_tputs.c term_edit_line.c com_list_ft.c \
	  term_write_line.c hist_list_ft.c print_command.c copy_mode.c \
	  copy_end_mode.c com_list_ft2.c lex_finish_line.c sh_signal_handler.c \
	  term_mv_cursor.c parse_build_com.c parse_find_error.c exec_list_ft.c \
	  sh_minishell.c get_next_line.c change_hist.c yank_line.c tab_mode.c \
	  hash_get_tab.c sh_builtin_hash.c

INCLUDE = -I includes/

FLAG = -Wall -Werror -Wextra

LIBRARIES = -L libft/ -L ft_printf -lft -lftprintf -ltermcap

CFILES = $(addprefix src/, $(SRC))

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	@gcc -c $(FLAG) $(INCLUDE) $(CFILES)
	@#@make -C libft/ fclean && make -C libft && make -C libft/ clean
	@#@make -C ft_printf/ fclean && make -C ft_printf && make -C ft_printf/ clean
	@gcc -o $(NAME) $(LIBRARIES) $(OBJ)
	@echo "\x1b[32;02m$(NAME) ready\x1b[0;m"

clean:
	@/bin/rm -f $(OBJ)
	@echo "\x1b[0;01mclean\x1b[0;m"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "\x1b[0;01mfclean\x1b[0;m"

re: fclean all
