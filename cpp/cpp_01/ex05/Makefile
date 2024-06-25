###################
## VARIABLES
NAME	= harl2.0
CFLAGS	= -Wall -Wextra -Werror -std=c++98 -g -Iincludes
CC		= c++
OBJDIR = ./build
SRCDIR = ./srcs

##################
## SOURCES

SRCS =	./main.cpp \
		$(shell find $(SRCDIR) -name "*.cpp")

OBJS = $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRCS))

###################
## RULES

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re