/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_subcmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 18:02:06 by tsanzey           #+#    #+#             */
/*   Updated: 2016/04/26 18:02:07 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "shell.h"

t_token		*ft_join_topar(t_token *tok)
{
	t_token	*tmp;
	t_token	*tmp1;
	char	*str;

	tmp = tok;
	while (tmp)
	{
		if (tmp->type == O_PAR)
		{
			tmp1 = tmp->next;
			if (tmp1->type == C_PAR)
				return (tok);
			tmp = tmp1->next;
			while (tmp && tmp->type != C_PAR)
			{
				str = tmp1->content;
				tmp1->type = SUBSHELL;
				tmp1->content = ft_strjoin(tmp1->content, tmp->content);
				tmp = pop_middle_token(tmp);
				free(str);
			}
		}
		tmp = tmp->next;
	}
	return (tok);
}

t_token 		*ft_subshell(t_token *tok)
{
	t_token	*tmp;

	tmp = tok;
	while (tmp)
	{
		if (tmp->type == O_PAR)
		{
			tok = ft_join_topar(tok);
			if (check_next_token(tok) != C_PAR)
				tok->next->tree = sh_lexer_parser(tok->next->content);
			tok = ft_token_removal(tok, O_PAR);
			tok = ft_token_removal(tok, C_PAR);
		}
		tmp = tmp->next;
	}
	return (tok);
}