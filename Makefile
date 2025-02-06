# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/10 15:49:58 by vvasiuko          #+#    #+#              #
#    Updated: 2025/01/29 16:39:08 by vvasiuko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
NAME_BONUS = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -Ilibft -g
# -fsanitize=address
LFLAGS = -lreadline -Llibft -lft
SRC = main.c garbage_collector.c environment.c \
	parser/parser.c parser/scanner.c parser/tokens.c parser/expander.c parser/syntax.c \
	builtins/builtin_exec.c builtins/cd.c  builtins/pwd.c builtins/echo.c builtins/env.c builtins/export.c builtins/unset.c \
	test.c
OBJ = $(SRC:.c=.o)
RM = rm -f

LIBFT_NAME = libft.a
LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)/$(LIBFT_NAME)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) $(LFLAGS) -o $(NAME) 

$(LIBFT):
	@make -C $(LIBFT_PATH)

%.o: %.c includes/minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)
	@make clean -C $(LIBFT_PATH)

fclean: clean
	$(RM) $(NAME)
	@make fclean -C $(LIBFT_PATH)

re: fclean all

.PHONY: all clean fclean re
