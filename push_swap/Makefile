# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/11 16:20:49 by tdeverge          #+#    #+#              #
#    Updated: 2023/01/09 14:31:41 by tdeverge         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

####################
## VARIABLES

NAME = push_swap
NAME_BONUS = checker
CFLAGS = -Wall -Wextra -Werror -Iincludes -Iincludes/libft
CC = clang
LIB = ./includes/libft/libft.a

####################
## SOURCES

SRCS = ./main.c \
	   ./sources/parsing/normalize.c \
	   ./sources/sorting/pivot.c \
	   ./sources/sorting/sort.c \
	   ./sources/sorting/small_inputs.c \
	   ./sources/sorting/big_inputs.c \

SRCS_COMMON = 	./sources/sorting/utils.c \
	   			./sources/parsing/parsing.c \
	   			./sources/parsing/duplicate.c \
	   			./sources/parsing/stack.c \
	   			./sources/parsing/error.c \
				./sources/operations/utils.c \
				./sources/operations/helpers.c \
				./sources/operations/swap.c \
				./sources/operations/push.c \
				./sources/operations/rotate.c \
				./sources/operations/reverse_rotate.c \

SRCS_BONUS =	./checker_bonus.c \
				./sources/checker/operations_bonus.c \

OBJS = $(SRCS:.c=.o)

OBJS_COMMON = $(SRCS_COMMON:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

#####################
## RULES

all : $(NAME)

$(NAME): $(OBJS) $(OBJS_COMMON)
	make -C ./includes/libft
	$(CC) $(CFLAGS) $(OBJS) $(OBJS_COMMON) -o $(NAME) $(LIB)

bonus : $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS) $(OBJS_COMMON)
	make -C ./includes/libft
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(OBJS_COMMON) -o $(NAME_BONUS) $(LIB)

.c.o:
	$(CC) $(CFLAGS) -g -c $< -o ${<:.c=.o}

clean:
	rm -rf $(OBJS)
	rm -rf $(OBJS_COMMON)
	rm -rf $(OBJS_BONUS)
	make -C ./includes/libft clean

fclean: clean
	rm -rf $(NAME)
	rm -rf $(NAME_BONUS)
	make -C ./includes/libft fclean

re: fclean all

.PHONY: all clean fclean re bonus
