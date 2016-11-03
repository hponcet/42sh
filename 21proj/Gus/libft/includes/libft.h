/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 14:56:31 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/18 22:04:45 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include "get_next_line.h"
# include "ft_hash.h"

/*
************** Fonctions de gestion de memoire brut ***************
*/
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *restrict dst, const void *restrict src,
					size_t n);
void				*ft_memmove(void *dst, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memccpy(void *restrict dst, const void *restrict src,
					int c, size_t n);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
/*
************** Fonctions de gestion de string ***************
*/
char				*ft_strmerge(char *a, char *b);
char				*ft_strnew(size_t size);
char				*ft_strcut(char *str, int len);
char				*ft_strdup(const char *s1);
char				*ft_strdelc(char *str, int i);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strcat(char *restrict dest, const char *restrict src);
int					ft_strcmp(const char *s1, const char *s2);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
char				*ft_strrepchar(char *str, char c, char newc);
char				*ft_strrvrs(char *str);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
size_t				ft_strlen(char const *s);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_joinf(char *format, ...);
char				*ft_strncat(char *restrict s1, const char *restrict s2,
					size_t n);
size_t				ft_strlcat(char *restrict dst, const char *restrict src,
					size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *big, const char *little);
int					ft_atoi(const char *str);
char				*ft_itoa(int n);
char				*ft_strnstr(const char *big, const char *little,
					size_t len);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				**ft_strsplit(char const *s, char c);
char				*ft_strtrim(char const *s);
int					ft_printf(const char *format, ...);
/*
*************** Fonctions de gestion de tableaux ****************
*/
void				ft_tabdel(char **table);
/*
************** Fonctions de gestion de characters ***************
*/
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_cindex(char *str, char c);
int					ft_cindex_rev(char *str, char c);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putnstr(char const *s, int n);
void				ft_putendl(char const *s);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putchar_fd(char c, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putnbr(int n);
void				ft_putnbr_base(long int n, char *base);
/*
************** Fonctions de detections ***************
*/
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					match(char *str1, char *str2);
int					nmatch(char *str1, char *str2);
/*
************** Structure basique *******************
*/
typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;
/*
*************** Fonctions pour listes chainees ***************
*/
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstaddend(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
int					ft_lstlen(t_list *list);
/*
***************** Fonctions Mathematiques *******************
*/
int					ft_abs(int i);
int					ft_rootsquare(int n);

#endif
