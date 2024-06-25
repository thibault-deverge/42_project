###################
## VARIABLES
NAME = ircserv
NAME_BONUS = bot
CFLAGS = -Wall -Wextra -Werror -std=c++98 -g -Iincludes
CC = c++
OBJDIR = ./build
OBJDIR_BONUS = ./build_bonus
SRCDIR = ./sources
BOTDIR = ./botdir

##################
## SOURCES

SRCS = ./main.cpp \
	$(shell find $(SRCDIR) -name "*.cpp")

OBJS = $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRCS))

SRCS_BONUS = $(shell find $(BOTDIR) -name "*.cpp")

OBJS_BONUS = $(patsubst %.cpp,$(OBJDIR_BONUS)/%.o,$(SRCS_BONUS))

###################
## RULES

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME_BONUS)

$(OBJDIR_BONUS)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(OBJDIR_BONUS)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re
