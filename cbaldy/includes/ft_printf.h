/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 14:56:27 by cbaldy            #+#    #+#             */
/*   Updated: 2016/01/29 15:26:51 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

typedef struct		s_options
{
	int				size;
	int				precision;
	int				width;
	int				diese;
	int				zero;
	int				moins;
	int				space;
	int				plus;
	int				dol;
	char			c;
	int				dot;
	int				fd;
}					t_op;

typedef struct		s_conv
{
	char			c;
	char			*base;
}					t_conv;

typedef struct		s_put
{
	char			id;
	int				(*f)(va_list);
}					t_put;

t_op				*g_op;

int					ft_printf(char *str, ...);
int					ft_convert(char *str, va_list ap, int i, int fd);
void				ft_putstr_fd(char const *s, int fd);
char				*ft_strdup(const char *s1);
char				*ft_strnew(size_t size);
size_t				ft_strlen(const char *var);
char				*ft_strchr(const char *s, int c);
void				ft_putchar_fd(char c, int fd);
int					ft_idprint(va_list ap2);
int					ft_sprint(va_list ap2);
int					ft_len_opt(char *opt);
int					ft_nu_arg(char *str, int i);
int					ft_atoi(const char *str);
t_op				*ft_read_option(char *str, int i);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_reconvert(unsigned long long nbr, char *base_to);
int					ft_putnbr_2(long long k);
char				*ft_strjoin(char const *s1, char const *s2);
int					ft_oprint(va_list ap2);
int					ft_ouxprint(va_list ap2);
int					ft_putnbr_3(unsigned long long k);
int					ft_print_z(va_list ap2);
int					ft_print_uz(va_list ap2);
int					ft_douprint(va_list ap2);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
int					ft_percentprint(va_list ap2);
unsigned long long	ft_power_cv(unsigned long long nb, int power_cv);
char				*ft_convert_base(char *nbr, char *base_fr, char *base_to);
int					ft_cprint(va_list ap2);
char				*ft_to_maj(char *nbr);
int					ft_pprint(va_list ap2);
int					ft_conv_wchar(int nb);
int					ft_invalid_conv(char *str, int i, int fd);
int					ft_nb_bytes(wchar_t *s, int all);
int					ft_nb_printed_bytes(wchar_t *s);
int					ft_read_precision(char *str);
char				*pf_strjoin(char *s1, char *s2, int fr);
char				*pf_strsub(char *s, unsigned int start, size_t len, int fr);
int					ft_dprintf(int fd, char *str, ...);

#endif
