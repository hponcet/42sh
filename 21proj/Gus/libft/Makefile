# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hponcet <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/17 19:57:28 by hponcet           #+#    #+#              #
#*   Updated: 2016/10/25 23:14:32 by hponcet          ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra

LIBFT_DIR = srcs/

EXEC =	srcs/ft_atoi.c \
		srcs/ft_bzero.c \
		srcs/ft_hash.c \
		srcs/ft_hash_new.c \
		srcs/ft_wchar_conv_bit.c \
		srcs/ft_isalnum.c \
		srcs/ft_isalpha.c \
		srcs/ft_isascii.c \
		srcs/ft_isdigit.c \
		srcs/ft_isprint.c \
		srcs/ft_itoa.c \
		srcs/ft_tabdel.c \
		srcs/ft_joinf.c \
		srcs/ft_lstadd.c \
		srcs/ft_lstaddend.c \
		srcs/ft_lstdel.c \
		srcs/ft_lstdelone.c \
		srcs/ft_lstiter.c \
		srcs/ft_lstmap.c \
		srcs/ft_lstnew.c \
		srcs/ft_lstlen.c \
		srcs/ft_memalloc.c \
		srcs/ft_memccpy.c \
		srcs/ft_memchr.c \
		srcs/ft_memcmp.c \
		srcs/ft_memcpy.c \
		srcs/ft_memdel.c \
		srcs/ft_memmove.c \
		srcs/ft_memset.c \
		srcs/ft_match.c \
		srcs/ft_nmatch.c \
		srcs/ft_putchar.c \
		srcs/ft_putchar_fd.c \
		srcs/ft_putendl.c \
		srcs/ft_putendl_fd.c \
		srcs/ft_rootsquare.c \
		srcs/ft_putnbr.c \
		srcs/ft_putnbr_fd.c \
		srcs/ft_putnbr_base.c \
		srcs/ft_putstr.c \
		srcs/ft_putnstr.c \
		srcs/ft_putstr_fd.c \
		srcs/ft_strcat.c \
		srcs/ft_strchr.c \
		srcs/ft_strclr.c \
		srcs/ft_strcmp.c \
		srcs/ft_strcpy.c \
		srcs/ft_strdel.c \
		srcs/ft_strdelc.c \
		srcs/ft_strdup.c \
		srcs/ft_strequ.c \
		srcs/ft_striter.c \
		srcs/ft_striteri.c \
		srcs/ft_strjoin.c \
		srcs/ft_strlcat.c \
		srcs/ft_strlen.c \
		srcs/ft_strmerge.c \
		srcs/ft_strcut.c \
		srcs/ft_strmap.c \
		srcs/ft_strmapi.c \
		srcs/ft_strncat.c \
		srcs/ft_strncmp.c \
		srcs/ft_strncpy.c \
		srcs/ft_strnequ.c \
		srcs/ft_strnew.c \
		srcs/ft_strnstr.c \
		srcs/ft_strrchr.c \
		srcs/ft_strrvrs.c \
		srcs/ft_strsplit.c \
		srcs/ft_strstr.c \
		srcs/ft_strsub.c \
		srcs/ft_strtrim.c \
		srcs/ft_strrvrs.c \
		srcs/ft_strrepchar.c \
		srcs/ft_cindex.c \
		srcs/ft_cindex_rev.c \
		srcs/ft_abs.c \
		srcs/ft_tolower.c \
		srcs/ft_toupper.c \
		srcs/get_next_line.c \
		srcs/ft_check_arg_list.c \
		srcs/ft_check_format.c \
		srcs/ft_check_type.c \
		srcs/ft_error.c \
		srcs/ft_error_d.c \
		srcs/ft_error_s.c \
		srcs/ft_error_u.c \
		srcs/ft_error_x.c \
		srcs/ft_init.c \
		srcs/ft_print.c \
		srcs/ft_print_list_arg_c.c \
		srcs/ft_print_list_arg_d.c \
		srcs/ft_print_list_arg_o.c \
		srcs/ft_print_list_arg_p.c \
		srcs/ft_print_list_arg_pc.c \
		srcs/ft_print_list_arg_s.c \
		srcs/ft_print_list_arg_u.c \
		srcs/ft_print_list_arg_x.c \
		srcs/ft_print_list_flags_ht.c \
		srcs/ft_print_list_str.c \
		srcs/ft_print_nchar.c \
		srcs/ft_printf.c \
		srcs/ft_tools_buf.c \
		srcs/ft_tools_format.c \
		srcs/ft_tools_lst.c \
		srcs/ft_tools_nbr.c \
		srcs/ft_tools_str.c \
		srcs/ft_wchar_conv_bit.c \
		srcs/ft_wchar_to_char.c

OBJECTS = $(EXEC:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	-@ar rc $(NAME) $(OBJECTS)
	-@ranlib $(NAME)
	@echo "Libft correctly created."

%.o: %.c
	-@$(CC) $(CFLAGS) -I ./includes -c $< -o $@

clean :
	-@rm -rf $(OBJECTS)

fclean: clean
	-@rm -rf $(NAME)
	@echo "Libft cleaned."

re: fclean all

proper: all clean
