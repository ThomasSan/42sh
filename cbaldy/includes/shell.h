/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 19:12:49 by cbaldy            #+#    #+#             */
/*   Updated: 2016/05/02 12:29:32 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "libft.h"
# include "ft_printf.h"
# include "struct_shell.h"
# include "get_next_line.h"
# include "ft_select.h"
# include "hash.h"
# include "lexer.h"
# include "parse_build_list.h"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <fcntl.h>
# include <limits.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <sys/ioctl.h>

# define HIST_SIZE 32

t_line_list		*str_to_line(char *str, t_line_list *first);
t_line_list		*line_list_dup(t_line_list *var);
int				line_list_free(t_line_list *first);
int				manage_search_hist(char *buf, t_line_list **first,
		t_hist_list **hist, int check);
int				exit_search_hist(t_line_list **first);
int				hist_print_line(char *s);
int				search_history(t_com_list *begin);
int				sh_builtin_history(char **com);
t_hist_list		*retrieve_history(int flag, t_line_list *first);
int				exit_completion(t_line_list *begin);
char			*cd_var_env(char *name);
int				clear_hist(t_hist_list **hist);
t_hist_list		*copy_hist(t_hist_list *hist);
int				sh_prompt(void);
int				sh_command(char **com);
int				sh_builtin_cd(char **com);
int				sh_builtin_env(char **com);
int				sh_builtin_setenv(char **com);
int				sh_builtin_unsetenv(char **com);
int				sh_builtin_exit(char **com);
int				ft_free_tab(char **arr);
char			*mod_strjoin(char *s1, char *s2, int fr);
char			*mod_strsub(char *s, unsigned int start, size_t len, int fr);
char			*mod_strtrim(char *s);
int				cd_exist_error(char *path, char *com, int flag);
char			*sh_get_env_var(char *var_name);
int				sh_add_var_env(char *name, char *value);
int				sh_rm_var_env(char *name);
int				sh_is_new_var(char *com);
int				sh_change_var_env(char *name, char *value);
char			*cd_get_path(char **com, int opt);
char			*cd_get_old_path(void);
char			*cd_print_path(char **com, char *n_path, int opt);
int				sh_getenv(char **com);
int				sh_set_env(char **env);
int				env_custom(char **com);
int				cd_substitution(char **com);
int				cd_update_env(char *old_path, char *new_path, int opt);

int				sh_set_term(void);
int				sh_get_term_fildes(void);
int				sh_reset_term(void);
int				ft_tputs(char *s, int nb_l, int flag);
int				term_edit_line(char *buf, int len, t_line_list **first,
		t_hist_list **hist);
t_com_list		*com_list_new(char value);
int				com_list_count(t_com_list *begin);
int				term_write_line(t_line_list **first, char buf,
		t_hist_list **hist);
char			*com_list_retrieve(t_com_list *begin);
int				*hist_list_new(t_hist_list **hist);
int				com_list_free(t_com_list *begin);
t_com_list		*com_list_dup(t_com_list *begin);
int				hist_change(int move, t_hist_list **hist, t_line_list **first);
int				print_command(t_com_list *new, char buf, t_line_list *first);
int				term_mv_horizontal(int move, t_line_list **first, int change);
int				copy_cut_mode(t_line_list **first, int mode);
int				copy_end_mode(t_line_list **first);
int				copy_paste(t_line_list **first);
t_com_list		*com_list_reconstruct(char *s);
int				com_list_remove(t_com_list *del, t_com_list **begin);
int				term_finish_line(t_line_list *first);
int				com_list_add(t_com_list **begin, t_com_list *new, int marge);
char			*com_list_join(t_com_list *begin);
int				term_mv_cursor(char buf, t_line_list **first);
t_exec_list		*parse_build_com(char *str);
int				parse_find_error(char *s);
t_exec_list		*exec_list_new(char *str, int connect);
int				exec_list_add(t_exec_list **begin, t_exec_list *new);
int				exec_list_count(t_exec_list *begin);
int				sh_exec_control(char *str);
int				sh_minishell(void);
int				yank_line(char c, t_line_list **first);
int				tab_mode(t_line_list **first);
t_tree			*sh_lexer_parser(char *str);
int				sh_execute(char **com);
int				sh_interpret(t_tree *root);
int				exec_pipe(t_tree *root);
int				exec_redout(t_tree *root);
char			*sh_get_exec_path(char *cmd);
int				sh_builtin_echo(char **com);
int				exec_redin(t_tree *root);
int				exec_and(t_tree *root);
int				exec_or(t_tree *root);
int				exec_end(t_tree *root);
void			sh_save_std_fd(void);
int				sh_reset_std_fd(void);
char			*sh_retrieve_cmd_line(t_line_list *first, int end);
char			*cd_get_path2(char *com);
t_line_list		*line_list_new(int marge);
char			*line_list_retrieve(t_line_list *first);
t_line_list		*line_list_dup(t_line_list *var);
int				line_list_free(t_line_list *first);
int				line_list_get_marge(t_line_list *first);
int				glob_it(char **glob, char *str);
char			*cd_env_cdpath(char **com, int dir);
char			**tabl_compl(char *path);
int				alias_ihome(char **path, int i);
int				alias_home(char **path);
int				exec_heredoc(t_tree *root);
int				heredoc_edit_line(char *buf, int len, t_line_list **first);
int				heredoc_write_line(t_line_list **first, char buf, char *eof);
int				*fd_save(void);
int				fd_reset(int *save);
char			*exec_backquotes(t_tree *root);
int				exec_free_root(t_tree *root);
int				parse_list_free(t_parse *head);
int				exec_subshell(t_tree *root);
int				get_bangged(char **str, t_line_list **first);
int				mini_finish_line(char *str);
int				escape_spec_cara(char **to_add);
int				hist_control_size(t_hist_list **hist);
int				heredoc_main(t_tree *root);

#endif
