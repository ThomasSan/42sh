# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbaldy <mail>                              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/07 16:13:53 by dbaldy            #+#    #+#              #
#    Updated: 2016/03/15 12:03:46 by dbaldy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

SRC = aux_shell.c change_dir.c env2.c env_bin.c main.c minus.c operand.c\
	  prompt.c command.c execute_command.c mypwd.c env.c list_ch.c ope_env.c\
	  list_param.c ft_select.c cursor_mvt.c read_key.c signal.c\
	  get_nb_row.c get_nb_col.c start_select.c aux.c map_key.c\
	  get_line_of_command.c line_edit.c read_line_command.c term_operations.c\
	  line_to_print.c suppr_elem.c histo_operations.c

LIB1 = libft/

LIB2 = ft_dprintf/

SRC2 = $(addprefix src/, $(SRC))

INCLUDE = -I include/

BIN = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@echo "\x1b[0;01mproceeding"
	@gcc $(FLAGS) -c $(SRC2) $(INCLUDE)
	@gcc -o $(NAME) $(BIN) -L $(LIB1) -L $(LIB2) -ltermcap -lft -lftprintf
	@echo "\x1b[32;02m$(NAME) done\x1b[0;m"

clean:
	@/bin/rm -rf $(BIN)
	@echo "\x1b[0;00mclean done"

fclean: clean
	@/bin/rm -rf $(NAME)
	@echo "\x1b[0;01mfclean done"

re: fclean all
