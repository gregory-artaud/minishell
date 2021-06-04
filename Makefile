# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gartaud <gartaud@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/14 22:19:13 by gartaud           #+#    #+#              #
#    Updated: 2021/06/04 09:41:33 by gartaud          ###   ########lyon.fr    #
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
DEPS		= $(shell find includes %.h -type f 2> /dev/null)
DEPS		+= $(addprefix $(LIB_DIR)/, \
					libft/libft.h)
SRC_DIR		= src/
FILES		= $(shell find src *.c -type f)
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
