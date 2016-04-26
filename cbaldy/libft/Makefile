# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/25 18:31:38 by cbaldy            #+#    #+#              #
#    Updated: 2016/04/26 12:44:25 by dbaldy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
	  ft_isdigit.c ft_isprint.c ft_memccpy.c ft_memchr.c ft_memcmp.c \
	  ft_memcpy.c ft_memmove.c ft_memset.c ft_strcat.c ft_strchr.c \
	  ft_strcmp.c ft_strcpy.c ft_strdup.c ft_strlcat.c ft_strlen.c \
	  ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnstr.c ft_strrchr.c \
	  ft_strstr.c ft_tolower.c ft_toupper.c ft_memalloc.c ft_memdel.c \
	 ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c \
	 ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c \
	 ft_strjoin.c ft_strtrim.c ft_putchar.c ft_putstr.c ft_putendl.c \
	 ft_putnbr.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
	 ft_putnbr_fd.c ft_strsplit.c ft_itoa.c ft_lstnew.c ft_lstdelone.c \
	 ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c \
	 ft_sort_integer_table.c ft_power.c ft_sqrt.c ft_is_prime.c \
	 ft_find_next_prime.c ft_convert_base.c ft_strtrunc.c ft_strjoin_multiple.c\
	 ft_replace_str.c ft_ireplace_str.c ft_freetab.c ft_array_push.c

SRC1 = ft_atoi.o ft_bzero.o ft_isalnum.o ft_isalpha.o ft_isascii.o \
	  ft_isdigit.o ft_isprint.o ft_memccpy.o ft_memchr.o ft_memcmp.o \
	  ft_memcpy.o ft_memmove.o ft_memset.o ft_strcat.o ft_strchr.o \
	  ft_strcmp.o ft_strcpy.o ft_strdup.o ft_strlcat.o ft_strlen.o \
	  ft_strncat.o ft_strncmp.o ft_strncpy.o ft_strnstr.o ft_strrchr.o \
	  ft_strstr.o ft_tolower.o ft_toupper.o ft_memalloc.o ft_memdel.o \
	 ft_strnew.o ft_strdel.o ft_strclr.o ft_striter.o ft_striteri.o \
	 ft_strmap.o ft_strmapi.o ft_strequ.o ft_strnequ.o ft_strsub.o \
	 ft_strjoin.o ft_strtrim.o ft_putchar.o ft_putstr.o ft_putendl.o \
	 ft_putnbr.o ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o \
	 ft_putnbr_fd.o ft_strsplit.o ft_itoa.o ft_lstnew.o ft_lstdelone.o \
	 ft_lstdel.o ft_lstadd.o ft_lstiter.o ft_lstmap.o \
	 ft_sort_integer_table.o ft_power.o ft_sqrt.o ft_is_prime.o \
	 ft_find_next_prime.o ft_convert_base.o ft_strtrunc.o ft_strjoin_multiple.o\
	  ft_replace_str.o ft_ireplace_str.o ft_freetab.o ft_array_push.o

all: $(NAME)

$(NAME):
	@gcc -c -Wall -Werror -Wextra $(SRC)
	@ar rc $(NAME) $(SRC1)
	@ranlib $(NAME)
	@echo "\x1b[0;01mlibft ready\x1b[0;m"

clean:
	@/bin/rm -f $(SRC1)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
