/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/15 11:04:02 by tsanzey           #+#    #+#             */
/*   Updated: 2015/12/23 13:48:25 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 1

int		get_next_line(int const fd, char **line);
int		get_line_len(int const fd, char **dst);
int		checknewline(char *s);
char	*del_line(char *s, int i);

#endif
