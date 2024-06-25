NAME	:= cub3D
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -g
CC		:= clang
LIBFT	:= ./libft
LIBMLX	:= ./minilibx

HEADERS	:= -I ./includes -I $(LIBMLX)/include -I $(LIBFT)/includes
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
OBJS_MLX	:= ${SRCS_MLX:.c=.o}

###########
## Sources

SRCS_MAND = ./main.c \
			./sources/render/generate_images.c \
			./sources/render/render_window.c \
			./sources/render/hook.c \

SRCS = 	./sources/parsing/parsing.c \
		./sources/utils/init.c \
		./sources/parsing/elements.c \
		./sources/parsing/textures.c \
		./sources/parsing/layers.c \
		./sources/parsing/map.c \
		./sources/parsing/validity_map.c \
		./sources/parsing/helpers.c \
		./sources/render/draw_background.c \
		./sources/render/draw_walls.c \
		./sources/render/move_player.c \
		./sources/render/rotate_player.c \
		./sources/render/collision.c \
		./sources/render/textures.c \
		./sources/utils/errors.c \
		./sources/utils/free.c \
		./sources/utils/helpers.c \
		./sources/utils/ft_insert_matrix.c \
		./sources/utils/convert_textures.c \

SRCS_BONUS =	./main_bonus.c \
				./sources/bonus/draw_fov_minimap_bonus.c \
				./sources/bonus/draw_minimap_bonus.c \
				./sources/bonus/generate_images_bonus.c \
				./sources/bonus/render_window_bonus.c \
				./sources/bonus/hook_bonus.c \
				./sources/bonus/draw_player_bonus.c \

OBJS = $(SRCS:.c=.o)

OBJS_MAND = $(SRCS_MAND:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

##########
## Rules

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4 --no-print-directory

$(NAME): $(OBJS) $(OBJS_MAND) $(OBJS_MLX)
	@make -C ./libft --no-print-directory
	@$(CC) $(CFLAGS) $(OBJS) $(OBJS_MAND) $(OBJS_MLX) $(LIBS) $(HEADERS) -o $(NAME) ./libft/libft.a

bonus : libmlx $(OBJS) $(OBJS_BONUS) $(OBJS_MLX)
	@rm -rf $(NAME)
	@make -C ./libft --no-print-directory
	@$(CC) $(CFLAGS) $(OBJS) $(OBJS_BONUS) $(OBJS_MLX) $(LIBS) $(HEADERS) -o $(NAME) ./libft/libft.a

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

clean:
	@rm -rf $(OBJS_MLX)
	@rm -rf $(OBJS) 
	@rm -rf $(OBJS_BONUS) 
	@rm -rf $(OBJS_MAND) 
	@rm -rf $(LIBMLX)/build
	@make -C ./libft clean --no-print-directory 

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(NAME_BONUS)
	@make -C ./libft fclean --no-print-directory

re: fclean all

.PHONY: all, clean, fclean, re, libmlx, bonus
