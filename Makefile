# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/10 15:49:58 by vvasiuko          #+#    #+#              #
#    Updated: 2025/01/25 14:17:14 by vvasiuko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
NAME_BONUS = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -Ilibft -g
LFLAGS = -lreadline -Llibft -lft
SRC = main.c garbage_collector.c environment.c
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

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)
	@make clean -C $(LIBFT_PATH)

fclean: clean
	$(RM) $(NAME)
	@make fclean -C $(LIBFT_PATH)

re: fclean all

.PHONY: all clean fclean re
