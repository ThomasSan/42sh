/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/23 15:42:46 by cbaldy            #+#    #+#             */
/*   Updated: 2016/04/23 18:54:57 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	heredoc_read_prompt(t_line_list **first, char *eof)
{
	int		len;
	int		i;
	char	buf[10];

	len = read(STDIN_FILENO, buf, 10);
	ft_bzero(&buf[len], 10 - len);
	i = 0;
	if ((len != 1 || buf[0] < 31 || buf[0] > 127) &&
			(len != 1 || buf[0] != 10))
		i = heredoc_edit_line(buf, len, first);
	else if (len == 1)
		i = heredoc_write_line(first, buf[0], eof);
	return (i);
}

static int	heredoc_remove_last(t_line_list **first)
{
	t_line_list	*tmp;

	tmp = NULL;
	if ((*first)->previous != NULL)
	{
		tmp = (*first)->previous;
		tmp->next = NULL;
	}
	(*first)->previous = NULL;
	com_list_free((*first)->begin);
	free(*first);
	*first = tmp;
	return (0);
}

static char	*heredoc_retrieve(t_line_list **first, int i)
{
	t_line_list	*tmp;
	char		*str;

	tmp = NULL;
	if (i == 3)
	{
		g_local->her = -1;
		line_list_free(*first);
		return (NULL);
	}
	else if (i == 10)
		heredoc_remove_last(first);
	if (*first == NULL)
		return (NULL);
	while (*first != NULL && (*first)->previous != NULL)
		*first = (*first)->previous;
	str = line_list_retrieve(*first);
	line_list_free(*first);
	return (str);
}

static char	*heredoc_prompt(char *eof)
{
	int			i;
	t_line_list	*first;

	sh_set_term();
	ft_tputs("cd", 1, 0);
	ft_dprintf(STDIN_FILENO, "heredoc> ");
	g_local->curs = 11;
	if ((first = line_list_new(10)) == NULL)
		return (NULL);
	i = 0;
	while (i != 10 && i != 3 && i != 4)
		i = heredoc_read_prompt(&first, eof);
	return (heredoc_retrieve(&first, i));
}

int		exec_heredoc(t_tree *root)
{
	char	*str;
	int		ret;
	int		fd[2];

	str = heredoc_prompt(root->cmd[0]);
	pipe(fd);
	ft_putstr_fd(str, fd[1]);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	ret = sh_interpret(root->right);
	if (str != NULL)
		free(str);
	close(fd[0]);
	sh_reset_std_fd();
	return (ret);
}
