#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <dirent.h>
# include <fcntl.h>
# include "libft.h"

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
	// SLASH,
	BACKSLASH,
	DOLLAR,
	// HASHTAG,
	MINUS,
	LESS_AND,
	GREAT_AND,
	AND_GREAT,
	// LESS_GREAT,
	D_PIPE,
	D_SAND,
	NUMBERS = 100,
	WHITESPACE = 200,
	COMMANDS = 300,
	FILENAME = 400,
	WORDS = -1
}					t_sym;

typedef	enum 		e_cmd
{
	CMD,
	LESS,
	GREAT,
	D_LESS,
	D_GREAT,
	L_AND,
	G_AND,
	AND_G,
	TUBES,
	AND_IF,
	OR_IF,
	END
}					t_cmd;

typedef struct 		s_tree
{
	struct s_tree	*left;
	struct s_tree	*right;
	char			**cmd;
	int				types;
	int				fd[2];
}					t_tree;

typedef struct 		s_token
{
	int				type;
	int				used;
	char			*content;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct 		s_parse
{
	char			**arg;
	int				type;
	struct s_parse	*next;
}					t_parse;

int					ft_isspace(int c);
char				*ft_catplus(char *s1, char *s2, char c);
t_parse				*ft_checking_syntax(t_token *tok);
t_token				*ft_tokeniser(char *s, t_token *head);
t_tree				*tree_generator(t_tree *head, t_token *tok);
int					check_next_token(t_token *tok);
int					check_prev_token(t_token *tok);
t_parse				*ft_push_cmd(t_parse *head, t_token *tok);
t_parse				*ft_analyse_token(t_parse *head, t_token *tok);
t_parse				*ft_push_output(t_parse *head, t_token *tok);
t_parse				*ft_push_input(t_parse *head, t_token *tok);
void				free_array(char **arr);
int					ft_command_isvalid(t_token *tok);
void				parse_error(char *s);
t_token				*ft_tild_expand(t_token *tok);
t_token				*pop_middle_token(t_token *tok);
t_token				*ft_variable_expand(t_token *tok);
t_parse				*sh_preparse(t_token *tok);
int					number_of_rows(t_token *tok);
t_token				*check_dollar(t_token *tok);
/*
**				Array of function pointer
*/
int					(*g_f[101])(t_token*);
void				ft_array_fun(void);
int					rules_for_pipes(t_token *tok);
int					rules_for_great(t_token *tok);
int					rules_for_less(t_token *tok);
int					rules_for_minus(t_token *tok);
int					rules_for_great_and(t_token *tok);
int					rules_for_less_and(t_token *tok);
int					rules_for_and_great(t_token *tok);
int					rules_for_orandif(t_token *tok);
int					rules_for_numbers(t_token *tok);
/*
**
*/

void				check_back_quotes(t_token *tok);
t_token				*ft_token_removal(t_token *tok, t_sym sym);
void				ft_display_tokens(t_token *tok);
int					ft_edit_useless(t_token *tok);
int					ft_next_token(char *s, int start, int type);
int					is_word_or(char *s, int i);
int					ft_token_type(char *s, int i);

#endif
