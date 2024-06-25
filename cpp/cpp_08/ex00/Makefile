###################
## VARIABLES
NAME = easy_find
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -g -Iincludes
CXX = c++
OBJDIR = ./build

##################
## SOURCES

SRCS = ./main.cpp \

OBJS = $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRCS))

###################
## RULES

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
