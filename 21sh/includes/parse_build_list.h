/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_build_list.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/26 15:18:02 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/26 19:50:29 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_BUILD_LIST_H
# define PARSE_BUILD_LIST_H

# include "shell.h"
# include "lexer.h"

t_parse		*parse_build_list(t_token *tok);
int			parse_get_cmd(t_parse **head, t_token *tok);
t_parse		*parse_list_new(char **arg, int type);
int			parse_list_pushback(t_parse *new, t_parse **head);
int			parse_get_redir(t_parse **head, t_token *tok);

#endif
