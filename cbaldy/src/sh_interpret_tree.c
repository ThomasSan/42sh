/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_interpret_tree.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 12:05:44 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/23 12:07:54 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_exec_list	g_exec_list[] = {
	{0, &exec_cmd},
	{2, &exec_redout},
	{5, &exec_pipe},
	{-1, NULL},
};

int			sh_interpret(t_tree *root)
{
	int		i;

	i = 0;
	while (g_exec_list[i].id != -1)
	{
		if (g_exec_list[i].id == root->types)
			g_exec_list[i].f(root);
		i++;
	}
	return (0);
}

int			sh_exec_tree(char *str)
{
	t_tree		*root;
	int			s[3];

	if ((root = sh_lexer_parser(str)) != NULL)
		ft_putendl("LEXER_PARSER: OK");
	s[0] = dup(STDIN_FILENO);
	s[1] = dup(STDOUT_FILENO);
	s[2] = dup(STDERR_FILENO);
	sh_interpret(root);
	dup2(s[0], STDIN_FILENO);
	dup2(s[1], STDOUT_FILENO);
	dup2(s[2], STDERR_FILENO);
	close(s[0]);
	close(s[1]);
	close(s[2]);
	return (0);
}
