###################
## VARIABLES
NAME	= dreamjob
CFLAGS	= -Wall -Wextra -Werror -std=c++98 -g
CC		= c++

##################
## SOURCES

SRCS =	./Account.cpp \
		./tests.cpp

OBJS = $(SRCS:.cpp=.o)

###################
## RULES

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.cpp=.o)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
