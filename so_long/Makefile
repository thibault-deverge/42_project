# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/15 22:39:21 by tdeverge          #+#    #+#              #
#    Updated: 2022/12/11 16:34:22 by tdeverge         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

####################
## VARIABLES

NAME = so_long
CFLAGS = -Wall -Wextra -Werror -Iincludes -Iincludes/lib/libft -Iincludes/lib/minilibx_linux
CC = clang
LIB = ./includes/lib/libft/libft.a \
	  ./includes/lib/minilibx-linux/libmlx.a

####################
## SOURCES

SRCS = ./main.c \
	   ./sources/helper/error.c \
	   ./sources/helper/clear.c \
	   ./sources/parsing/parsing.c \
	   ./sources/parsing/utils.c \
	   ./sources/parsing/check_arg.c \
	   ./sources/parsing/read_map.c \
	   ./sources/parsing/check_items.c \
	   ./sources/parsing/pathfinding.c \
	   ./sources/game/render.c \
	   ./sources/game/event.c \
	   ./sources/game/move.c \
	   ./sources/game/compare.c \
	   ./sources/game/enemy.c \

OBJS = $(SRCS:.c=.o)

####################
## RULES

all: $(NAME)

$(NAME): $(OBJS)
		make -C ./includes/lib/libft
		make -C ./includes/lib/minilibx-linux
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIB) -lXext -lX11

.c.o:
	$(CC) $(CFLAGS) -g -c $< -o ${<:.c=.o}

clean:
	rm -rf $(OBJS) 
	make -C ./includes/lib/libft clean 
	make -C ./includes/lib/minilibx-linux clean

fclean: clean
	rm -rf $(NAME)
	make -C ./includes/lib/libft fclean

re: fclean all

.PHONY: all clean fclean re
