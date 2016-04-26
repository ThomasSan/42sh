/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 19:13:53 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/15 19:41:54 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# define BUFF_SIZE 10

typedef struct			s_fd_list
{
	char				*str;
	int					fds;
	struct s_fd_list	*next;
}						t_st_list;

int						get_next_line(int const fd, char **line);
char					*ft_strchr(const char *s, int c);
char					*ft_strsub(char const *s, unsigned int start,
		size_t len);
char					*ft_strjoin(char const *s1, char const *s2);
size_t					ft_strlen(const char *var);
char					*ft_strnew(size_t size);
char					*ft_strdup(const char *str);

#endif
