# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/03 18:11:43 by tdeverge          #+#    #+#              #
#    Updated: 2022/11/14 20:58:32 by tdeverge         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

####################
## VARIABLES

NAME = libft.a
CC = clang
CFLAGS = -Wall -Wextra -Werror

####################
## SOURCES

SRCS =	./sources/conversion/ft_atoi.c \
		./sources/conversion/ft_tolower.c \
		./sources/conversion/ft_toupper.c \
		./sources/conversion/ft_itoa.c \
		./sources/checker/ft_isalnum.c \
		./sources/checker/ft_isalpha.c \
		./sources/checker/ft_isascii.c \
		./sources/checker/ft_isdigit.c \
		./sources/checker/ft_isprint.c \
		./sources/memory/ft_memchr.c \
		./sources/memory/ft_memcmp.c \
		./sources/memory/ft_memcpy.c \
		./sources/memory/ft_memmove.c \
		./sources/memory/ft_memset.c \
		./sources/memory/ft_bzero.c \
		./sources/memory/ft_calloc.c \
		./sources/string/ft_split.c \
		./sources/string/ft_strchr.c \
		./sources/string/ft_strdup.c \
		./sources/string/ft_strjoin.c \
		./sources/string/ft_strlcat.c \
		./sources/string/ft_strlcpy.c \
		./sources/string/ft_strlen.c \
		./sources/string/ft_strncmp.c \
		./sources/string/ft_strnstr.c \
		./sources/string/ft_strrchr.c \
		./sources/string/ft_strtrim.c \
		./sources/string/ft_substr.c \
		./sources/string/ft_striteri.c \
		./sources/string/ft_strmapi.c \
		./sources/print/ft_putchar_fd.c \
		./sources/print/ft_putstr_fd.c \
		./sources/print/ft_putendl_fd.c \
		./sources/print/ft_putnbr_fd.c \
		./sources/linked_list/ft_lstnew.c \
		./sources/linked_list/ft_lstadd_front.c \
		./sources/linked_list/ft_lstsize.c \
		./sources/linked_list/ft_lstlast.c \
		./sources/linked_list/ft_lstadd_back.c \
		./sources/linked_list/ft_lstdelone.c \
		./sources/linked_list/ft_lstclear.c \
		./sources/linked_list/ft_lstiter.c \
		./sources/linked_list/ft_lstmap.c \
		./sources/printf/ft_printf.c \
		./sources/printf/count.c \
		./sources/printf/identify.c \
		./sources/printf/print.c \
		./sources/get_next_line/get_next_line.c \
		./sources/get_next_line/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

####################
## RULES

all: $(NAME)
	
.c.o: 
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}
	
$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -rf $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -rf $(NAME) $(NAME_BONUS)
	
re: fclean all

.PHONY: all clean fclean re
