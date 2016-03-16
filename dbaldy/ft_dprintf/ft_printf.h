/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 16:12:35 by dbaldy            #+#    #+#             */
/*   Updated: 2016/02/08 15:51:12 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <string.h>
# include <stdlib.h>
# include <stdint.h>
# include <wchar.h>
# include <unistd.h>
# include <time.h>
# define PRC 16
# define OPT_H 1
# define OPT_HH 2
# define OPT_L 4
# define OPT_LL 8
# define OPT_J 32
# define OPT_Z 64
# define OPT_MIN 128
# define OPT_PLUS 256
# define OPT_DIESE 512
# define OPT_ZERO 1024
# define OPT_SPACE 2048

typedef struct			s_ptr_fct
{
	char				c;
	void				(*f)(va_list);
}						t_ptr;

void					ft_putchar_fd(char c, int fd);
char					ft_tolower(int c);
char					*replace_end(char *str, char c);
char					*get_winch2(char *str, char *tmp);
void					treat_nul(void);
char					*complete_special(char *str, int size,
		const char *type);
void					ft_putk(va_list ap);
char					*treat_b_diese(char *str);
void					ft_putb(va_list ap);
char					*treat_b(char *str);
char					*ft_putzb(va_list ap);
char					*ft_putbsf(va_list ap);
char					*ft_puthhb(va_list ap);
char					*ft_puthb(va_list ap);
char					*ft_putjb(va_list ap);
char					*ft_putllb(va_list ap);
char					*ft_putlb(va_list ap);
int						nombre_digit(char *str);
int						check_base(char *str, int base);
char					*precision(char *str, int base);
void					check_print(char *str);
char					*check_size(char *str);
char					*format_s(char *str);
void					get_winch(va_list ap);
char					*treatwint(wint_t c);
char					*initialize_str(wint_t c);
char					*get_majx(va_list ap);
char					*fill_str(void);
char					*ft_putosf(va_list ap);
char					*treat_p(char *str);
void					treat_unconform(char c);
void					flags_3(char *str);
char					*ft_putzo(va_list ap);
char					*putuz(va_list ap);
char					*ft_putzd(va_list ap);
char					*treat_u(char *str);
void					ft_putu(va_list ap);
char					*putusf(va_list ap);
char					*putuj(va_list ap);
char					*putull(va_list ap);
char					*putul(va_list ap);
char					*putuhh(va_list ap);
char					*putuh(va_list ap);
int						max(int a, int b);
int						ft_strcmp(const char *s1, const char *s2);
char					*get_char(va_list ap);
char					*long_char(va_list ap);
char					*treat_c(char *str);
char					*ft_upper(char *str);
char					*complete_behind(char *str, int size, const char *type);
char					*treat_d2(char *str);
char					*ft_strjoinclrdv(char **s1, const char *s2);
char					*ft_strjoinclrdr(const char *s1, char **s2);
char					*treat_o(char *str);
int						ft_toupper(int c);
int						size_sign(char *st);
char					*treat_majx(char *str);
char					*ft_putsfx(va_list ap);
char					*treat_x(char *str);
char					*treat_d(char *str);
char					*complete(char *str, int size, const char *type);
char					*ft_putjo(va_list ap);
char					*ft_putllo(va_list ap);
char					*ft_putlo(va_list ap);
char					*ft_putho(va_list ap);
char					*ft_puthho(va_list ap);
char					*ft_putdc(va_list ap);
char					*ft_putsf(va_list ap);
char					*ft_putj(va_list ap);
char					*ft_putzx(va_list ap);
char					*ft_puthhx(va_list ap);
char					*ft_puthx(va_list ap);
char					*ft_puthhmajx(va_list ap);
char					*ft_puthmajx(va_list ap);
char					*ft_putjx(va_list ap);
char					*ft_putllg(va_list ap);
char					*ft_putllx(va_list ap);
char					*ft_putllmajx(va_list ap);
char					*ft_putsh(va_list ap);
char					*ft_itoa_adv_u(unsigned long long nb, char *base);
char					*ft_putlg(va_list ap);
char					ft_putuc(va_list ap);
char					*ft_putlx(va_list ap);
char					*ft_putlmajx(va_list ap);
void					flags_1(char *str);
void					flags_2(char *str);
void					flags_4(char *str);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_itoa_adv(long long nb, char *base);
void					ft_putp(va_list ap);
void					ft_putloo(va_list ap);
void					ft_putmajx(va_list ap);
void					ft_putx(va_list ap);
char					*ft_itoa_base(int nb, char *base);
void					ft_putint(va_list ap);
void					ft_puts(va_list ap);
void					ft_putc(va_list ap);
unsigned int			nb_ch(long long nb);
char					*ft_strdup(const char *s);
int						ft_strlen(const char *s);
void					ft_putint(va_list ap);
void					ft_putendl(const char *str);
char					*ft_strsub(char const *s, unsigned int i,
		unsigned int j);
int						conforme(const char *fm, int j);
char					*correspond(char c);
char					*ft_strchr(const char *s, int c);
char					*ft_strrchr(const char *s, int c);
void					ft_putchar(char c);
void					convert_data(va_list ap, char *str);
char					analyse(char fm, const char *check);
void					ft_putnbr(long long nb);
void					ft_putstr(const char *str);
int						ft_printf(const char *fm, ...);
int						tr_data(va_list ap, const char *fm, int j);
long long				ft_atoi(char *s);
long long				ft_atoi_base(char *s, int base);
void					ft_putstr_fd(char *str, int fd);
int						g_print;
int						g_trait;
int						g_precision;
int						g_fd;
int						g_width;
#endif
