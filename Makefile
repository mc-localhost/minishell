# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/10 15:49:58 by vvasiuko          #+#    #+#              #
#    Updated: 2025/02/16 18:18:37 by vvasiuko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
NAME_BONUS = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -Ilibft -g -fsanitize=address
LFLAGS = -lreadline -Llibft -lft
SRC = main.c garbage_collector.c environment.c \
	parser/parser.c \
	parser/scanner.c parser/scanner_handlers.c \
	parser/tokens.c parser/heredoc.c \
	parser/expander.c parser/expander_utils.c \
	parser/syntax.c \
	parser/final_tokens.c parser/final_tokens_redir.c parser/final_tokens_utils.c\
	parser/iter.c \
	builtins/builtin_exec.c builtins/cd.c  builtins/pwd.c builtins/echo.c builtins/env.c builtins/export.c builtins/unset.c \
	gnl/get_next_line.c \
	executor.c \
	safe_libft/ft_itoa_safe.c safe_libft/ft_split_safe.c safe_libft/ft_strdup_safe.c safe_libft/ft_strjoin_safe.c safe_libft/ft_strlcpy_safe.c safe_libft/ft_substr_safe.c
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
