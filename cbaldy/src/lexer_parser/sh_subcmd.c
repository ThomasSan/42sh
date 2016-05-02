/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_subcmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 18:02:06 by tsanzey           #+#    #+#             */
/*   Updated: 2016/04/28 14:11:33 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "ft_printf.h"
#include "shell.h"

char	*ft_strjoin2(char *s1, char const *s2)
{
	char	*str;
	size_t	i[2];

	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (str == NULL)
		return (NULL);
	i[0] = 0;
	i[1] = 0;
	while (s1[i[0]])
	{
		str[i[0]] = s1[i[0]];
		i[0]++;
	}
	while (s2[i[1]])
	{
		str[i[0] + i[1]] = s2[i[1]];
		i[1]++;
	}
	str[i[0] + i[1]] = '\0';
	free(s1);
	return (str);
}

int				sub_count(t_token *tok)
{
	int	i;

	i = 0;
	while(tok)
	{
		if (tok->type == O_PAR)
			i++;
		tok = tok->next;
	}
	return(i);
}

int				init_tmp(t_token **tmp1, t_token **tmp)
{
	(*tmp1) = (*tmp)->next;
	if ((*tmp1)->type == C_PAR || (*tmp1)->type == O_PAR)
		return (0);
	(*tmp1)->type = SUBSHELL;
	(*tmp) = (*tmp1)->next;
	return (1);
}

t_token			*ft_join_topar(t_token *tok, int nb)
{
	t_token	*tmp;
	t_token	*tmp1;

	tmp = tok;
	while (tmp)
	{
		if (tmp->type == O_PAR)
		{
			if (init_tmp(&tmp1, &tmp) == 0)
				return(tok);
			while (tmp && nb > 0)
			{
				if (tmp && tmp->type == C_PAR)
					nb--;
				if (nb > 0)
				{
					tmp1->content = ft_strjoin2(tmp1->content, tmp->content);
					tmp = pop_middle_token(tmp);
				}
			}
		}
		else
			tmp = tmp->next;
	}
	return (tok);
}

t_token			*ft_subshell(t_token *tok)
{
	t_token	*tmp;
	int		sub_shells;

	tmp = tok;
	sub_shells = sub_count(tok);
	if (sub_shells == 0)
		return (tok);
	while (tmp)
	{
		if (tmp->type == O_PAR)
		{
			tok = ft_join_topar(tok, sub_shells);
			tok = ft_token_removal(tok, O_PAR);
			tok = ft_token_removal(tok, C_PAR);
		}
		tmp = tmp->next;
	}
	return (tok);
}
