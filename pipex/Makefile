# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/13 17:44:18 by tdeverge          #+#    #+#              #
#    Updated: 2023/01/23 15:08:20 by tdeverge         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

####################
## VARIABLES

NAME = pipex
NAME_BONUS = pipex_bonus
CFLAGS = -Wall -Wextra -Werror -Iincludes -Iincludes/libft
CC = clang
LIB = ./includes/libft/libft.a

####################
## SOURCES

SRCS = ./main.c \
	   ./sources/fork.c \
	   ./sources/utils.c \
	   ./sources/helpers.c \
	   ./sources/error.c \

SRCS_BONUS = ./bonus/main_bonus.c \
			 ./bonus/fork_bonus.c \
			 ./bonus/parity_bonus.c \
			 ./bonus/utils_bonus.c \
			 ./bonus/helpers_bonus.c \
			 ./bonus/errors_bonus.c \
			 ./bonus/exit_bonus.c \

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

####################
## RULES

all: $(NAME)

$(NAME): $(OBJS)
	make -s -C ./includes/libft
	$(CC) $(CFLAGS) -g $(OBJS) -o $(NAME) $(LIB)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS)
	make -s -C ./includes/libft
	$(CC) $(CFLAGS) -g $(OBJS_BONUS) -o $(NAME_BONUS) $(LIB)

.c.o:
	$(CC) $(CFLAGS) -g -c $< -o $(<:.c=.o)

clean:
	rm -rf $(OBJS)
	rm -rf $(OBJS_BONUS)
	make -s -C ./includes/libft clean

fclean: clean
	rm -rf $(NAME)
	rm -rf $(NAME_BONUS)
	make -s -C ./includes/libft fclean

re: fclean all

.PHONY: all clean fclean re bonus
