#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <dirent.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "get_next_line.h"

typedef enum 		e_sym
{
	QUOTES,
	SINGLE_QUOTES,
	BACK_QUOTES,
	DIPLE_R,
	DOUBLE_R,
	DIPLE_L,
	DOUBLE_L,
	PIPE,
	SEMICOL,
	AMPERSAND,
	TILD,
	SLASH,
	BACKSLASH,
	DOLLAR,
	HASHTAG,
	MINUS,
	// SPACE = 99,
	WORDS = -1
}					t_sym;

typedef struct 		s_tree
{
	struct s_tree	*next;
	struct s_tree	*prev;
	char			*content;
	int				types;
}					t_tree;

typedef struct 		s_token
{
	int				type;
	int				used;
	char			*content;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

char				*rules_for_strings(t_token *tok);
char				*rules_for_semicol(char *s);
t_token				*ft_checking_syntax(t_token *tok);
t_token				*ft_tokeniser(char *s, t_token *head);
t_tree				*tree_generator(t_tree *head, t_token *tok);
t_token				*ft_checking_syntax(t_token *tok);
#endif