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
#include "parser.h"
#include "tree_build_cmd.h"

t_tree		*sh_lexer_parser(char *str)
{
	t_token	*tok;

	tok = NULL;
	tok = ft_tokeniser(str, tok);
	tok = ft_checking_syntax(tok);
	return (tree_build_cmd(tok));
}
