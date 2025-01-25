# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/10 15:49:58 by vvasiuko          #+#    #+#              #
#    Updated: 2024/12/20 16:29:15 by vvasiuko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_BONUS = pipex_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -g
SRC_ADD = libft/ft_split.c libft/ft_strdup.c libft/ft_strjoin.c libft/ft_strlen.c libft/ft_strncmp.c\
	utils/cleanup.c utils/error.c utils/paths.c
SRC = $(SRC_ADD) pipex.c
SRC_BONUS = libft/ft_split.c libft/ft_strdup.c libft/ft_strjoin.c libft/ft_strlen.c libft/ft_strncmp.c\
bonus/bonus.c bonus/error_bonus.c bonus/paths_bonus.c
OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)
RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c includes/pipex.h
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_BONUS)
	$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJ_BONUS)

bonus/%.o: bonus/%.c includes/pipex_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(OBJ_BONUS)

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus
