# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gartaud <gartaud@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/14 22:19:13 by gartaud           #+#    #+#              #
#    Updated: 2021/04/15 09:21:06 by gartaud          ###   ########lyon.fr    #
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
DEPS		= $(shell find includes *.h -type f 2> /dev/null)
DEPS		+= $(addprefix $(LIB_DIR)/, \
					libft/libft.h)
SRC_DIR		= src/
FILES		= $(shell find src *.c -type f)
OBJ 		= $(FILES:%.c=%.o)
VFLAGS		= --leak-check=full --track-origins=yes

all: $(LIBFT) $(MLX) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ $(LIBFT) $(MLX) $(LFLAGS) -o $@

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

.PHONY: clean fclean all re
