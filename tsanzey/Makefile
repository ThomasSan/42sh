NAME = Lexer
SRC = main.c lexer.c parser.c grammar.c ft_token_recognition.c get_next_line.c\
 ft_free.c ft_syntaxical.c ft_push_tree.c ft_misc.c pipe_grammar.c ft_grammar_great.c\

OBJ = $(SRC:%.c=obj/%.o)

CXX = clang
CXXFLAGS = -Wall -Werror -Wextra

INC = -I includes
LIB = libft/

all: $(NAME)

$(NAME): obj $(OBJ)
	@make -s -C $(LIB)
	@$(CXX) $(CXXFLAGS) -o $@ $(OBJ) $(INC) -L$(LIB) -lft
	@echo "\\033c\033[1;32m\r Use ./Lexer \" list of cmd \"\033[0m"

obj/%.o: %.c
	@$(CXX) $(CXXFLAGS) $(INC) -o $@ -c $< -I$(LIB)

obj:
	@mkdir -p obj/

clean:
	@rm -rf obj

fclean: clean
	@echo "\\033c\033[0;31m deleting Obj && Project\033[0m"
	@sleep 1
	@rm -rf $(NAME)

re: fclean all

.PHONY: fclean all clean re
