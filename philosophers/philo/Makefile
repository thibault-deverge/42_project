# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/05 12:06:47 by tdeverge          #+#    #+#              #
#    Updated: 2023/03/08 15:06:46 by tdeverge         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

####################
## VARIABLES

NAME	= philo
CFLAGS	= -Wall -Wextra -Werror -g -pthread -Iincludes
CC		= clang
INCDIR	= includes

####################
## SOURCES

SRCS = 	./main.c \
		./sources/parsing/data.c \
		./sources/parsing/rules.c \
		./sources/parsing/philosophers.c \
		./sources/parsing/mutexes.c \
		./sources/execution/launch.c \
		./sources/execution/routine_philo.c \
		./sources/execution/routine_supervisor.c \
		./sources/execution/checker.c \
		./sources/utils/ft_atoi_rule.c \
		./sources/utils/time.c \
		./sources/utils/free.c \

OBJS	= $(SRCS:.c=.o)

####################
## RULES

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)
	
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
