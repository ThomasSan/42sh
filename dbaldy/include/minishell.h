/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/30 15:34:41 by dbaldy            #+#    #+#             */
/*   Updated: 2016/02/26 18:38:54 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <dirent.h>
# include <sys/stat.h>
# include <limits.h>
# include "libft.h"
# include "ft_printf.h"

typedef struct			s_env_list
{
	char				*var;
	int					nb;
	struct s_env_list	*next;
}						t_env;

int						verif_env_value(char *var, char *str);
int						to_lower(char **str);
int						get_prompt(void);
void					reduce_next(t_env *buf);
int						get_aliases(char **tabl);
char					*verif_exe(char *command, int type);
char					*direct_path(char *str);
char					*substitute(char *first, char *second);
char					*my_aliases(char *operand);
char					*ft_replace_str(char *old, char *str, char *replace);
int						size_list(t_env *debut);
int						execute_command(char **tabl, char *path);
void					free_env(t_env **debut);
int						count_char(char *str, char c);
int						fct_env(char **tabl);
char					*last_mbr(char **tab);
char					**retrieve_env(t_env *debut);
void					shell_level(t_env *debut);
int						chg_env_tab(char **tab, int a);
char					*free_quotes(char *str);
char					**ft_splitquote(char *s, char c);
char					*ft_replacestr(char *old, char *to_check, char *alias);
int						sortie(char **tab);
void					treat_minus(char *str);
char					*clean_pwd(char *ret);
char					*ft_mypwd(char *operand);
void					prev_alias(char **tab, int size);
void					home_alias(char **tab, int size);
char					*check_length(char *to_check, char *path);
char					**my_pwd(char *pwd);
int						check_rights_all(char *path);
char					*get_pwd(char **tab);
char					*get_operand(char **tab);
int						check_opt(char *option);
char					*get_path(char *operand);
void					change_pwd(char *operand, char *pwd, char **tab);
void					change_prompt(char *str);
int						check_existence(char *str);
void					change_env_var(char *name, char *str);
char					*get_env_var(char *name);
int						change_dir(char **tabl);
void					replace_tab(char **env, char **tab, int size);
void					copy_tab(char **tab, char **env);
int						size_tab(char **tab);
t_env					*get_env(char **env, char *name);
void					unset_env(char *str);
int						print_env(t_env *env);
void					add_env(char *str);
char					*find_path(char **tabl);
int						g_ret;
char					*g_prompt;
t_env					*g_env;
char					*g_operand;
char					*g_err;
char					*g_print_ch;
#endif
