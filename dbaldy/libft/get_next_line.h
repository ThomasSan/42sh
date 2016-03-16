/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 13:40:07 by dbaldy            #+#    #+#             */
/*   Updated: 2016/02/17 10:37:50 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 1024
# include <stdlib.h>
# include <unistd.h>

typedef struct		s_list
{
	int				fno;
	char			*str;
	struct s_list	*next;
}					t_lc;

char				*ft_strnew(size_t len);
int					get_next_line(int const fd, char **line);
char				*ft_strjoin(char const *s1, char const *s2);
void				ft_strclr(const char *s);
void				ft_putendl(char *str);
char				*ft_strsub(char *s, int debut, int size);
char				*ft_strchr(char *s, int c);
char				*ft_strdup(char *s);
int					ft_strlen(char *str);
int					ft_strcmp(char *s1, char *s2);
#endif
