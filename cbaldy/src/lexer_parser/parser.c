/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 11:06:02 by tsanzey           #+#    #+#             */
/*   Updated: 2016/03/03 11:06:04 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// t_tree	*tree_generator(t_tree *head, t_token *tok)
// {
// 	char	*str;

// 	str = NULL;
// 	head = NULL;
// 	while (tok)
// 	{
// 		if (tok->type == WORDS)
// 		{
// 			head = ft_push_cmd(head, tok);
// 			while (tok && tok->type == WORDS)
// 				tok = tok->next;
// 		}
// 		else
// 		{
// 			head = ft_analyse_token(head, tok);
// 			tok = tok->next;
// 		}
// 	}
// 	return (head);
// }
