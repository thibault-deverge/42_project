# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/11 14:38:20 by tdeverge          #+#    #+#              #
#    Updated: 2022/10/17 00:21:41 by tdeverge         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

########################
## VARIABLES

NAME = libftprintf.a
CFLAGS = -Wall -Wextra -Werror 
CC = gcc

########################
## SOURCES

SRCS = ft_printf.c \
	   srcs/identify.c \
	   srcs/count.c \
	   srcs/print.c

OBJS = $(SRCS:.c=.o)

########################
## RULES

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)
	
.c.o:
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
