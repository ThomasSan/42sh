# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/14 14:42:25 by cbaldy            #+#    #+#              #
#    Updated: 2016/03/26 19:33:59 by dbaldy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

SRC = main.c sh_set_term.c sh_read_prompt.c sh_command.c sh_builtin_cd.c \
	  sh_builtin_env.c ft_1_aux.c sh_builtin_exit.c cd_exist_error.c \
	  sh_builtin_setenv.c sh_add_var_env.c sh_builtin_unsetenv.c \
	  cd_get_path.c sh_set_env.c env_custom.c cd_substitution.c \
	  sh_interpret_tree.c ft_tputs.c term_edit_line.c com_list_ft.c \
	  term_write_line.c hist_list_ft.c print_command.c copy_mode.c \
	  copy_end_mode.c com_list_ft2.c lex_finish_line.c sh_signal_handler.c \
	  term_mv_cursor.c sh_minishell.c get_next_line.c change_hist.c yank_line.c \
      exec_redin_redout.c exec_pipe_and_or.c sh_get_exec_path.c \
	  sh_builtin_echo.c hash_get_tab.c sh_builtin_hash.c sh_execute.c \
	  sh_retrieve_cmd_line.c \
      sh_builtin_history.c

TAB = tab_mode.c tab_select.c tab_nb_col.c tab_nb_row.c tab_cursor_mvt.c \
	  tab_line_management.c tab_complete_line.c tab_prepare_select.c\
      tab_list_path.c tab_string_match.c tab_supp.c 

LEX = lexer.c parser.c ft_token_recognition.c ft_free.c ft_syntaxical.c \
	  ft_push_tree.c ft_misc.c pipe_grammar.c ft_great_grammar.c \
	  ft_input_correct.c tree_ft.c tree_build_cmd.c \
	  ft_isspace.c ft_catplus.c sh_lexer_parser.c ft_expansion.c \
	  ft_variable_expand.c sh_preparse.c grammar.c

INCLUDE = -I includes/

FLAG = -Wall -Werror -Wextra

LIBRARIES = -L libft/ -L ft_printf -lft -lftprintf -ltermcap

CFILES = $(addprefix src/, $(SRC))
CLEX = $(addprefix src/lexer_parser/, $(LEX))
CTAB = $(addprefix src/completion/, $(TAB))

OBJ = $(SRC:.c=.o)
OBJ2 = $(LEX:.c=.o)
OBJ3 = $(TAB:.c=.o)

all: $(NAME)

$(NAME):
	@gcc -c $(FLAG) $(INCLUDE) $(CFILES) $(CLEX) $(CTAB)
	@#@make -C libft/ fclean && make -C libft && make -C libft/ clean
	@#@make -C ft_printf/ fclean && make -C ft_printf && make -C ft_printf/ clean
	@gcc -o $(NAME) $(LIBRARIES) $(OBJ) $(OBJ2) $(OBJ3)
	@echo "\x1b[32;02m$(NAME) ready\x1b[0;m"

clean:
	@/bin/rm -f $(OBJ) $(OBJ2) $(OBJ3)
	@echo "\x1b[0;01mclean\x1b[0;m"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "\x1b[0;01mfclean\x1b[0;m"

re: fclean all
