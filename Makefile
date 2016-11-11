# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/04/26 11:46:03 by fkoehler          #+#    #+#              #
<<<<<<< HEAD
#*   Updated: 2016/11/07 21:00:22 by hponcet          ###   ########.fr       *#
=======
#    Updated: 2016/11/09 14:55:39 by fkoehler         ###   ########.fr        #
>>>>>>> Flav
#                                                                              #
# **************************************************************************** #

vpath %.c ./src ./src/builtins

SRC = buffer.c \
	  builtins_error.c \
	  builtins_check.c \
	  cd.c \
	  check_pipes.c \
	  check_redir.c \
	  cmd_check_input.c \
	  cmd_handling.c \
	  cmd_interpreting.c \
	  cmd_parsing.c \
	  cmd_storage.c \
	  cursor.c \
	  echo.c \
	  env.c \
	  env_tools.c \
	  environ.c \
	  error.c \
	  exec_bin.c \
	  exit.c \
	  fd_handling.c \
	  forking.c \
	  free.c \
	  free_btree.c \
	  heredoc.c \
	  hist_storage.c \
	  history.c \
	  input_cut_copy.c \
	  input_delete_keys.c \
	  input_handling.c \
	  keys_parsing.c \
	  line_moves_1.c \
	  line_moves_2.c \
	  lst_tools.c \
	  main.c \
	  print.c \
	  prompt.c \
	  redirection.c \
	  setenv.c \
	  signals.c \
	  str_tools.c \
	  strsplit_args.c \
	  str_subsplit_arg.c \
	  term_settings.c \
	  unsetenv.c

NAME = 42sh

FLAGS = -Wall -Werror -Wextra -g -fsanitize=address

LIBDIR = ./libft/

INCLUDES = $(LIBDIR)includes/

LIB = $(LIBDIR)libft.a

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
<<<<<<< HEAD
		@gcc $(FLAGS) -L$(LIBDIR) $(OBJ) -lft -ltermcap -o $@
		@echo "\033[0;32m21sh compilation done !\033[0;m"
=======
		@gcc $(FLAGS) $(OBJ) -L$(LIBDIR) -lft -ltermcap -o $@
		@echo "\033[0;32m42sh compilation done !\033[0;m"
>>>>>>> Flav

$(LIB):
	@make -C $(LIBDIR)

%.o: %.c
	@gcc $(FLAGS) -c $< -I . -I $(INCLUDES)

clean:
	@rm -f $(OBJ)
	@echo "\033[0;32mObject files deleted !\033[0;m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[0;32mExecutable deleted !\033[0;m"

re: fclean all
