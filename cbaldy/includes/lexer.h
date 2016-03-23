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
	HASHTAG,
	MINUS,
	LESS_AND,
	GREAT_AND,
	// LESS_GREAT,
	NUMBERS = 100,
	WHITESPACE = 200,
	WORDS = -1
}					t_sym;

typedef	enum 		e_cmd
{
	CMD,
	I_REDIR,
	O_REDIR,
	TUBES
}					t_cmd;

/*
cmd = 0;
< = 1;
> = 2;
<< = 3;
>> = 4;
<& = 5;
&> = 6;
>& = 7;
pipe = 8;
&& = 9;
|| = 10;
; = 11;
*/

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

typedef struct		s_env
{
	char			*name;
	char			*val;
	struct s_env	*next;
}					t_env;

int					ft_isspace(int c);
char				*ft_catplus(char *s1, char *s2, char c);
void				ft_start_cmd(char **cmd, t_env *env, int fd[2]);
void				ft_start_cmd2(char **cmd, t_env *env, int fd[2]);
char				*rules_for_strings(t_token *tok);
char				*rules_for_semicol(char *s);
t_token				*ft_checking_syntax(t_token *tok);
t_token				*ft_tokeniser(char *s, t_token *head);
t_tree				*tree_generator(t_tree *head, t_token *tok);
t_token				*ft_checking_syntax(t_token *tok);
int					check_next_token(t_token *tok);
int					check_prev_token(t_token *tok);
t_tree				*ft_push_cmd(t_tree *head, t_token *tok);
t_tree				*ft_analyse_token(t_tree *head, t_token *tok);
t_tree				*ft_push_output(t_tree *head);
t_tree				*ft_push_input(t_tree *head);
void				free_array(char **arr);
int					ft_command_isvalid(t_token *tok);
void				parse_error(char *s);
/*
**				Array of function pointer
*/
int					(*g_f[20])(t_token*);
void				ft_array_fun(void);
int					rules_for_pipes(t_token *tok);
int					rules_for_great(t_token *tok);

#endif
