# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/14 14:42:25 by cbaldy            #+#    #+#              #
#    Updated: 2016/02/15 10:43:35 by cbaldy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC = ft_printf.c ft_putstr_fd.c ft_strdup.c ft_strnew.c ft_strlen.c \
	  ft_strchr.c ft_idprint.c ft_sprint.c ft_1_aux.c ft_atoi.c \
	  ft_strcmp.c ft_read_opt.c ft_convert_base.c ft_strjoin.c \
	  ft_adv_putnbr.c ft_ouxprint.c ft_douprint.c ft_strsub.c \
	  ft_other_conv_print.c ft_cprint.c ft_wputchar.c ft_2_aux.c \
	  ft_putchar_fd.c ft_dprintf.c

SRC1 = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	@gcc -c -Wall -Werror -Wextra $(SRC)
	@ar rc $(NAME) $(SRC1)
	@ranlib $(NAME)
	@echo "\x1b[0;01mlibftprintf.a ready\x1b[0;m"

clean:
	@/bin/rm -f $(SRC1)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
