# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gartaud <gartaud@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/14 22:19:13 by gartaud           #+#    #+#              #
#    Updated: 2021/06/11 07:51:35 by gartaud          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
DEPS_DIR	= includes
LIB_DIR		= lib
LIBFT_DIR	= $(LIB_DIR)/libft
LIBFT		= $(LIBFT_DIR)/libft.a
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -O3 \
				-I ./$(DEPS_DIR) -I ./$(LIBFT_DIR)
LFLAGS		= -ltermcap
DEPS		= includes/defs.h \
				includes/execution.h \
				includes/minishell.h
DEPS		+= $(addprefix $(LIB_DIR)/, \
					libft/libft.h)
SRC_DIR		= src/
FILES		= src/error_interpreter/print_error.c \
				src/executer/builtins/b_cd.c \
				src/executer/builtins/b_echo.c \
				src/executer/builtins/b_env.c \
				src/executer/builtins/b_exit.c \
				src/executer/builtins/b_export/b_export.c \
				src/executer/builtins/b_export/display_export.c \
				src/executer/builtins/b_export/free_export.c \
				src/executer/builtins/b_pwd.c \
				src/executer/builtins/b_unset.c \
				src/executer/builtins/builtins_utils.c \
				src/executer/do_pipe.c \
				src/executer/exec_cmd.c \
				src/executer/exec_signals.c \
				src/executer/execute_file.c \
				src/executer/execute_file_utils.c \
				src/executer/executer.c \
				src/executer/pipe_utils.c \
				src/executer/redirect_utils.c \
				src/executer/redirect_utils2.c \
				src/executer/redirect_utils3.c \
				src/executer/run_pipe.c \
				src/generate_dot/generate_dot.c \
				src/init_shell.c \
				src/lexer/lexer.c \
				src/lexer/process_env.c \
				src/lexer/process_specials.c \
				src/lexer/process_specials_utils.c \
				src/lexer/tokenize.c \
				src/lexer/tokenize_redirect.c \
				src/lexer/tokenize_utils.c \
				src/lexer/tokenize_utils2.c \
				src/parser/clear_ast.c \
				src/parser/fill_arg.c \
				src/parser/fill_cmd.c \
				src/parser/parser.c \
				src/parser/parser_utils.c \
				src/reader/controller.c \
				src/reader/controller_utils.c \
				src/reader/reader.c \
				src/reader/termcaps.c \
				src/reader/termcaps_utils.c \
				src/set_current_dir.c \
				src/shell_utils.c \
				src/signal.c \
				minishell.c
OBJ 		= $(FILES:%.c=%.o)
VFLAGS		= --leak-check=full --track-origins=yes

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ $(LIBFT) $(LFLAGS) -o $@

$(LIBFT):
	make -sC $(LIBFT_DIR)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make -sC $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(LIB_DIR)/$(LIBFT)
	make -sC $(LIBFT_DIR) fclean

re: fclean all

norme:
	norminette $(FILES) $(DEPS)

.PHONY: clean fclean all re
