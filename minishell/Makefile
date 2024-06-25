####################
## VARIABLES

NAME	= minishell
CFLAGS	= -Wall -Wextra -Werror -I$(INCDIR) -Ilibft -g
CC	= clang
LIBFT = ./libft/libft.a
INCDIR	= includes

####################
## SOURCES

SRCS =	./main.c \
		./sources/parsing/main_parsing.c \
		./sources/parsing/prompt/prompt.c \
		./sources/parsing/environment/get_environment.c \
		./sources/parsing/pre_parsing/pre_parsing.c \
		./sources/parsing/pre_parsing/argument_manager.c \
		./sources/parsing/pre_parsing/utils.c \
		./sources/parsing/parsing_commands/parse_commands.c \
		./sources/parsing/parsing_commands/redirections.c \
		./sources/parsing/parsing_commands/utils.c \
		./sources/builtins/echo/echo.c \
		./sources/builtins/pwd/pwd.c \
		./sources/builtins/env/env.c \
		./sources/builtins/unset/unset.c \
		./sources/builtins/cd/cd.c \
		./sources/builtins/exit/exit.c \
		./sources/builtins/export/export.c \
		./sources/builtins/export/key.c \
	    ./sources/execution/main_execution.c \
		./sources/execution/handle_cases/redirections.c \
		./sources/execution/handle_cases/builtins.c \
		./sources/execution/handle_cases/heredoc.c \
		./sources/execution/handle_cases/utils.c \
		./sources/execution/pipex/commands.c \
		./sources/execution/pipex/fork.c \
		./sources/signal/signal.c \
		./sources/signal/status.c \
		./sources/signal/heredoc_signal.c \
		./sources/utils/environment/convert_environment.c \
		./sources/utils/environment/add_variable.c \
		./sources/utils/environment/modify_content.c \
		./sources/utils/environment/ascii.c \
		./sources/utils/environment/getter.c \
		./sources/utils/command/initialize_command.c \
		./sources/utils/command/is_last_command.c \
		./sources/utils/command/pid.c \
		./sources/utils/IO/close.c \
		./sources/utils/general/ft_atoll.c \
		./sources/utils/general/ft_sepjoin.c \
		./sources/utils/general/ft_joinpath.c \
    	./sources/utils/general/ft_insert_matrix.c \
		./sources/utils/error/std_error.c \
		./sources/utils/error/personalized_error.c \
		./sources/utils/free/free_linked_list.c \
		./sources/utils/free/free_matrices.c \

OBJS	= $(SRCS:.c=.o)

####################
## RULES

%.o:%.c
		$(CC) -c $< -o $@ $(CFLAGS)

all: $(NAME)

$(NAME): $(OBJS)
	make -s -C ./libft
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) -lreadline
	
clean:
	rm -f $(OBJS)
	make -s -C ./libft clean

fclean: clean
	rm -f $(NAME)
	make -s -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re
