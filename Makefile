# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/04/26 11:46:03 by fkoehler          #+#    #+#              #
#*   Updated: 2016/11/22 15:12:40 by hponcet          ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

NAME = 42sh

FLAGS = -Wall -Werror -Wextra -g

vpath %.c ./src ./src/builtins

SRC = buffer.c \
	  builtins_error.c \
	  builtins_check.c \
	  bltn_history.c \
	  bltn_history_opt.c \
	  bltn_hsearch.c \
	  cd.c \
	  check_pipes.c \
	  check_redir.c \
	  cmd_check_input.c \
	  cmd_handling.c \
	  cmd_interpreting.c \
	  cmd_parsing.c \
	  cmd_storage.c \
	  compl.c \
	  compl_display.c \
	  compl_getinfo.c \
	  compl_getpath.c \
	  compl_key.c \
	  compl_str.c \
	  cursor.c \
	  echo.c \
	  env.c \
	  env_tools.c \
	  environ.c \
	  exec_bin.c \
	  exit.c \
	  exit_status.c \
	  fd_handling.c \
	  forking.c \
	  free.c \
	  free_btree.c \
	  hash.c \
	  hash_bin.c \
	  hash_new.c \
	  heredoc.c \
	  hist_storage.c \
	  hist_file.c \
	  hist_check.c \
	  history.c \
	  input_cut_copy.c \
	  input_delete_keys.c \
	  input_handling.c \
	  input_tools.c \
	  keys_parsing.c \
	  line_moves_1.c \
	  line_moves_2.c \
	  lst_tools.c \
	  main.c \
	  main_parsing.c \
	  print.c \
	  prompt.c \
	  redirection.c \
	  setenv.c \
	  signals.c \
	  special_char.c \
	  str_tools.c \
	  strsplit_args.c \
	  str_subsplit_arg.c \
	  term_settings.c \
	  unsetenv.c \
	  ft_back_quote.c	\
	  ft_tools_back_quote.c	\
	  ft_error.c

# FILES
OBJS	= $(SRC:.c=.o)
O2		= $(addprefix $(OPATH), $(OBJS))

# DIRECTORIES
LIBFT	= ./libft/
OPATH	= ./obj/
INC		= ./includes/
LIBINC	= $(LIBFT)$(INC)
LIB		= $(LIBFT)libft.a

# PROCESS
all: $(NAME)

$(NAME): $(OBJS) $(LIB)
	@gcc $(FLAGS) $(O2) -L$(LIBFT) -lft -ltermcap -I$(INC) -o $(NAME)
	@echo "\033[0;32m42sh compilation done !\033[0;m"

$(LIB):
	@echo "\033[0;32mWaiting, libft is in compilation...\033[0;m"
	@make -C $(LIBFT)

%.o: %.c
	@gcc $(FLAGS) -c $< -I $(INC) -I $(LIBINC) -o $@
	@mv $@ $(OPATH)

clean:
	@rm -f $(O2)
	@echo "\033[0;32mObject files deleted !\033[0;m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[0;32mExecutable deleted !\033[0;m"
	-@make fclean -C $(LIBFT)
	@echo "\033[0;32mLibft cleaned.\033[0;m"

re: fclean all
