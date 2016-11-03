/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 01:13:18 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/21 19:11:13 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "ft_colors.h"
# include "libft.h"
# include <stdarg.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct		s_print
{
	char			*str;
	char			*flags;
	int				len;
	int				prec;
	int				mod;
	char			conv;
	struct s_print	*next;
}					t_print;

typedef struct		s_nchar
{
	int				last;
	int				len;
	struct s_nchar	*next;
}					t_nchar;

char				*g_bufret;
int					g_lenret;
int					g_pi;
int					g_null;
int					g_err;
t_nchar				*g_addrncharlst;
int					g_lastindex;

/*
** ft_init.c
*/
void				ft_init_g(void);
void				ft_init_wchar_mask(char **abit, char **bbit,
					char **cbit, char **dbit);
/*
** ft_check_format.c
*/
t_print				*ft_check(const char *format);
t_print				*ft_check_format(const char *format);
t_print				*ft_check_arg(const char *format);

/*
** ft_check_type.c
*/
unsigned long long	ft_check_utype(t_print *list, va_list ap);
long long			ft_check_type(t_print *list, va_list ap);

/*
** ft_check_arg_list.c
*/
t_print				*ft_check_arg_conv(const char *format, t_print *list);
t_print				*ft_check_arg_flags(const char *format, t_print *list);
t_print				*ft_check_arg_mod(const char *format, t_print *list);
t_print				*ft_check_arg_len(const char *format, t_print *list);
t_print				*ft_check_arg_prec(const char *format, t_print *list);

/*
** ft_print.c
*/
void				ft_print(t_print *list, va_list ap);
void				ft_print_list_arg(t_print *list, va_list ap);

/*
** ft_error.c
*/
void				ft_error(t_print *list);
void				ft_error_flags(char c, char conv);
void				ft_error_len(int len, char conv);
void				ft_error_conv(char conv);

/*
** ft_error_s.c
*/
void				ft_error_mins(t_print *list);
void				ft_error_majs(t_print *list);
void				ft_arg_s_ret_null(void);

/*
** ft_error_u.c
*/
void				ft_error_minu(t_print *list);
void				ft_error_maju(t_print *list);

/*
** ft_error_d.c
*/
void				ft_error_mind(t_print *list);
void				ft_error_majd(t_print *list);
void				ft_error_i(t_print *list);

/*
** ft_print_nchar.c
*/
t_nchar				*ft_new_list_nchar(void);
void				ft_putstr_nchar(char const *s);
void				ft_lst_addend_nchar(void);

/*
** ft_print_list_str.c
*/
void				ft_print_list_str(t_print *list);
char				ft_print_list_str_escseq(char c);

/*
** ft_print_list_arg_s.c
*/
void				ft_print_list_arg_s(t_print *list, va_list ap);
void				ft_print_list_arg_mins(t_print *list, char *str);
char				*ft_print_list_arg_mins_ht(t_print *list, char *buf);
void				ft_print_list_arg_majs(t_print *list, wchar_t *wstr);

/*
** ft_print_list_arg_pc.c
*/
void				ft_print_list_arg_pc(t_print *list);

/*
** ft_print_list_arg_c.c
*/
void				ft_print_list_arg_c(t_print *list, va_list ap);

/*
** ft_print_list_arg_d.c
*/
void				ft_print_list_arg_d(t_print *list, va_list ap);
void				ft_print_list_arg_d_flags(t_print *list, char *str);
void				ft_nbr_buf_zero(char *buf, char *str);
char				*ft_nbr_buf_esp(int j);
char				*ft_nbr_prec(t_print *list, char *str);

/*
** ft_print_list_arg_o.c
*/
void				ft_print_list_arg_o(t_print *list, va_list ap);

/*
** ft_print_list_arg_x.c
*/
void				ft_print_list_arg_x(t_print *list, va_list ap);
char				*ft_print_list_arg_x_prec(t_print *list, char *str);
unsigned long long	ft_check_umod_error(t_print *list, unsigned long long i);

/*
** ft_print_list_arg_p.c
*/
void				ft_print_list_arg_p(t_print *list, va_list ap);

/*
** ft_print_list_arg_u.c
*/
void				ft_print_list_arg_u(t_print *list, va_list ap);

/*
** ft_print_list_flags_ht.c
*/
char				*ft_print_list_flags_ht_x(t_print *list, char *buf);
char				*ft_print_list_flags_ht_o(t_print *list, char *buf);

/*
** ft_wchar_to_char.c
*/
char				*ft_wchar(wchar_t w);
char				*ft_wchar_complete(char *str);
void				ft_wchar_write(char *str, char *mask);
char				*ft_wchar_conv_bit(char *str);
int					ft_wchar_octlen(char *str);

/*
** ft_wchar_conv_bit.c
*/
void				ft_wchar_conv_bit1(char *str, int i, char *buf);
void				ft_wchar_conv_bit2(char *str, int i, char *buf);
void				ft_wchar_conv_bit3(char *str, int i, char *buf);
void				ft_wchar_conv_bit4(char *str, int i, char *buf);

/*
** ft_tools_buf.c
*/
void				ft_str_buf_to_bufret(char *buf);
char				*ft_str_buf_len_prec(t_print *list, char *str);
char				*ft_nbr_buf_len_prec(t_print *list, char *str);
char				*ft_tools_buf_new_zero(int i);

/*
** ft_tools_nbr.c
*/
char				*ft_itoa_base_ll(long long nbr, char *base, t_print *list);
char				*ft_itoa_base_ul(unsigned long long nbr, char *base);
int					ft_countnbr(int nb);
long				ft_power(long i, long j);

/*
** ft_tools_str.c
*/
char				*ft_str_tools_len_char(int i);
char				*ft_str_tools_wflags_char(char *buf, char *str,
					t_print *list);
char				*ft_str_tools_mflags_char(char *buf, char *str,
					t_print *list);
/*
** ft_tools_ustr.c
*/
unsigned char		*ft_ustrnew(size_t size);
size_t				ft_ustrlen(const unsigned char *s);

/*
** ft_tools_lst.c
*/
t_print				*ft_lst_new(void);
void				ft_lst_addend(t_print **list, t_print *new);
void				ft_print_print(t_print *tmp);

/*
** ft_tools_format.c
*/
int					ft_cnindex(char *str, char c, int i);
int					ft_check_next_perc(const char *format);

/*
** MOD***
** l  =	1
** ll =	2
** h  =	3
** hh =	4
** j  =	5
** z  =	6
** ******
** FLAGS**
** 0  =	 #
** 1  =	 -
** 2  =	 +
** 3  =  0
** 4  = sp
** *******
*/

#endif
