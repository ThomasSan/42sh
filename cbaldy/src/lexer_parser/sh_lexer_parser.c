/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 16:53:20 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/22 17:01:39 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "lexer.h"
#include "tree_build_cmd.h"

t_tree		*sh_lexer_parser(char *str)
{
	t_token	*tok;

	tok = NULL;
	tok = ft_tokeniser(str, tok);
	tok = ft_checking_syntax(tok);
	return (tree_build_cmd(tok));
}

// tab[0] = ls;
// tab[1] = -la;
// tab[3] = /;
// tab[4] = NULL;
// garder les seprators;
// cd ~/work
/*
int		i;
char 	*str;

if ((i = sh_is_new_var("VAR_NAME")) >= 0)
	str = ft_strdup(&(ft_strchr(g_env[i], '=')[1]));
*/

//Dans cet ordre :
// 1/ tild expansion
// 2/ changer var $""
// 3/ remove spaces
// 4/ remove quotes