#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2016/04/15 00:42:52 by hponcet           #+#    #+#             *#
#*   Updated: 2016/11/02 15:57:07 by hponcet          ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

NAME = 21sh

CC = gcc

CFLAGS = -Wall -Wall -Wextra

SRC =	ft_ast.c \
		ft_chain.c \
		ft_alias.c \
		ft_alias_file.c \
		ft_chain_tools.c \
		ft_chain_add.c \
		ft_char.c \
		ft_cmd.c \
		ft_cmd_split.c \
		ft_cmd_v.c \
		ft_cursor_pos.c \
		ft_debug.c \
		ft_debug_2.c \
		ft_display.c \
		ft_cindex.c \
		ft_dollar.c \
		ft_getfd.c \
		ft_history.c \
		ft_hsearch.c \
		ft_init.c \
		ft_key.c \
		ft_glob.c \
		ft_glob_sortchain.c \
		ft_glob_make.c \
		ft_glob_path.c \
		ft_hash_bin.c \
		ft_compl.c \
		ft_compl_key.c \
		ft_compl_display.c \
		ft_compl_getinfo.c \
		ft_compl_getpath.c \
		ft_compl_str.c \
		ft_key_bs.c \
		ft_key_ctrl_d.c \
		ft_key_del.c \
		ft_key_directional.c \
		ft_key_down.c \
		ft_key_enter.c \
		ft_key_home.c \
		ft_key_opt_copy.c \
		ft_key_opt_directional.c \
		ft_key_shift_dir_left.c \
		ft_key_shift_dir_right.c \
		ft_key_up.c \
		ft_quotes.c \
		ft_redir.c \
		ft_redir_tools.c \
		ft_redir_double_right.c \
		ft_redir_fd_left.c \
		ft_redir_fd_right.c \
		ft_redir_heredoc.c \
		ft_redir_heredoc_new.c \
		ft_redir_heredoc_tools.c \
		ft_redir_simple_right.c \
		ft_sh_name.c \
		ft_sh_check_opt.c \
		ft_signal.c \
		ft_signal_onexec.c \
		ft_term.c \
		ft_window_size.c \
		main.c \
		ms_builtin_cd.c \
		ms_builtin_env.c \
		ms_builtin_setenv.c \
		ms_builtin_unsetenv.c \
		ms_exec.c \
		ms_get.c \
		ms_get_cmd.c \
		ms_parse_cmd.c \
		ms_search.c

OBJECTS = $(addprefix $(SRCS), $(SRC:.c=.o))

LIBFT = ./libft/

LIB = libft.a

SRCS = ./srcs/

INC = ./includes/

LIB_FILE = $(addprefix $(LIBFT), $(LIB))

$(NAME): $(OBJECTS) $(LIB_FILE)
	-@$(CC) $(CFLAGS) $(OBJECTS) -L $(LIBFT) -ltermcap -lft -I$(INC) -o $(NAME)
	@echo "21sh ready to use !"

all: $(NAME)

$(LIB_FILE):
	@echo "Waiting, libft is in compilation..."
	-@make proper -C $(LIBFT)

%.o: %.c
	-@$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

clean :
	-@rm -rf $(OBJECTS)

fclean: clean libfclean
	-@rm -rf $(NAME)
	@echo "Binarie deleted."
	-@make fclean -C $(LIBFT)
	@echo "Libft cleaned."

libfclean:
	-@make fclean -C $(LIBFT)

libclean :
	-@make clean -C $(LIBFT)

re: libfclean fclean all

proper: all libfclean clean
