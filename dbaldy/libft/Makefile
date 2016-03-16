# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbaldy <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/25 19:28:59 by dbaldy            #+#    #+#              #
#    Updated: 2016/02/26 13:03:31 by dbaldy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SOURCE = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
		 ft_isdigit.c ft_isprint.c ft_memccpy.c ft_memchr.c ft_memcmp.c\
		 ft_memcpy.c ft_memmove.c ft_memset.c ft_freetab.c\
		 ft_strcat.c ft_strchr.c ft_strcmp.c ft_strcpy.c ft_strdup.c\
		 ft_strlcat.c ft_strlen.c ft_strncat.c ft_strncmp.c ft_strncpy.c\
		 ft_strnstr.c ft_strrchr.c ft_strstr.c ft_tolower.c ft_toupper.c\
		 ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c\
		 ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c\
		 ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c ft_strsplit.c\
		 ft_itoa.c ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c\
		 ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
		 ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c\
		 ft_lstmap.c ft_power.c ft_fact.c ft_sort_integer.c ft_is_prime.c\
		 ft_find_next_prime.c get_next_line.c get_nbr.c ft_freetab.c\
		 ft_strtrunc.c ft_strjoin_multiple.c ft_replacestr.c ft_splitquote.c\
		 ft_strsplit_whitespace.c count_char.c ft_replace_str.c\
		 size_until_char.c

BINAIRE = ft_atoi.o ft_bzero.o ft_isalnum.o ft_isalpha.o ft_isascii.o \
		 ft_isdigit.o ft_isprint.o ft_memccpy.o ft_memchr.o ft_memcmp.o\
		 ft_memcpy.o ft_memmove.o ft_memset.o ft_freetab.o\
		 ft_strcat.o ft_strchr.o ft_strcmp.o ft_strcpy.o ft_strdup.o\
		 ft_strlcat.o ft_strlen.o ft_strncat.o ft_strncmp.o ft_strncpy.o\
		 ft_strnstr.o ft_strrchr.o ft_strstr.o ft_tolower.o ft_toupper.o\
		 ft_memalloc.o ft_memdel.o ft_strnew.o ft_strdel.o ft_strclr.o\
		 ft_striter.o ft_striteri.o ft_strmap.o ft_strmapi.o ft_strequ.o\
		 ft_strnequ.o ft_strsub.o ft_strjoin.o ft_strtrim.o ft_strsplit.o\
		 ft_itoa.o ft_putchar.o ft_putstr.o ft_putendl.o ft_putnbr.o\
		 ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o ft_putnbr_fd.o\
		 ft_lstnew.o ft_lstdelone.o ft_lstdel.o ft_lstadd.o ft_lstiter.o\
		 ft_lstmap.o ft_power.o ft_fact.o ft_sort_integer.o ft_is_prime.o\
		 ft_find_next_prime.o get_next_line.o get_nbr.o ft_strtrunc.o\
		 ft_strjoin_multiple.o ft_replacestr.o ft_splitquote.o\
		 ft_strsplit_whitespace.o count_char.o ft_replace_str.o\
		 size_until_char.o


FLAGS = -Wall -Wextra -Werror -c

all: $(NAME) 

$(NAME):
	@gcc $(FLAGS) $(SOURCE)
	@ar rc $(NAME) $(BINAIRE)
	@ranlib $(NAME)
	@echo "libft done"

clean:
	@/bin/rm -rf $(BINAIRE)
	
fclean: clean
	@/bin/rm -rf $(NAME)

re: fclean all
