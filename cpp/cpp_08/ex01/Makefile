###################
## VARIABLES
NAME = span
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -g -Iincludes
CXX = c++
OBJDIR = ./build
SRCDIR = ./sources

##################
## SOURCES

SRCS = ./main.cpp \
		$(shell find $(SRCDIR) -name "*.cpp")

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
