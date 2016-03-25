/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_interpret_tree.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 12:05:44 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/25 16:17:24 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_exec_list	g_exec_list[] = {
	{LESS, &exec_redin},
	{GREAT, &exec_redout},
	{D_LESS, &exec_redin},
	{D_GREAT, &exec_redout},
	{TUBES, &exec_pipe},
	{AND_IF, &exec_and},
	{OR_IF, &exec_or},
	{END, &exec_end},
	{-1, NULL},
};

void		sh_save_std_fd(void)
{
	g_std_fd[0] = dup(STDIN_FILENO);
	g_std_fd[1] = dup(STDOUT_FILENO);
	g_std_fd[2] = dup(STDERR_FILENO);
}

void		sh_reset_std_fd(void)
{
	dup2(g_std_fd[0], STDIN_FILENO);
	dup2(g_std_fd[1], STDOUT_FILENO);
	dup2(g_std_fd[2], STDERR_FILENO);
}

int			sh_interpret(t_tree *root)
{
	int		i;
	int		ret;

	ret = -1;
	if (root->types == CMD)
		ret = sh_execute(root->cmd);
	i = 0;
	while (g_exec_list[i].id != -1 && ret == -1)
	{
		if (g_exec_list[i].id == root->types)
			ret = g_exec_list[i].f(root);
		i++;
	}
	if (root != NULL && root->cmd != NULL)
		ft_free_tab(root->cmd);
	if (root != NULL)
		free(root);
	return (ret);
}

int			sh_exec_tree(char *str)
{
	t_tree		*root;
	char		*ret;

	if ((root = sh_lexer_parser(str)) == NULL)
		return (0);
	sh_save_std_fd();
	ret = ft_itoa(sh_interpret(root));
	if ((sh_change_var_env("?", ret)) == -1)
		sh_add_var_env("?", ret);
	free(ret);
	sh_reset_std_fd();
	close(g_std_fd[0]);
	close(g_std_fd[1]);
	close(g_std_fd[2]);
	return (0);
}
