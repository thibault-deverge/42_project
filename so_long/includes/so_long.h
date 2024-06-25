/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 22:48:55 by tdeverge          #+#    #+#             */
/*   Updated: 2022/12/11 15:37:04 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

/* ********************************************* */
/* 					MACRO                        */
/* ********************************************* */
# define EMPTY_MAP		"Map is empty"
# define TOO_SMALL		"Map is too small."
# define NO_WALLS		"Map is not surrounded by walls."
# define NO_RECTANGLE	"Map is not a rectangle."
# define WRONG_SYMBOLS	"Map contains wrong symbols."
# define WRONG_ARGS		"Number of arguments is invalid."
# define WRONG_EXT		"Extension is invalid."
# define WRONG_PATH		"Path is not valid."
# define PLAYER_ERR		"Number of player is invalid."
# define EXIT_ERR		"Number of exit is invalid."
# define COLL_ERR		"Not enough collectibles."
# define MEM_ERR		"Memory allocation failed."

/* ********************************************* */
/* 					INCLUDES                     */
/* ********************************************* */
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <time.h>
# include "./lib/minilibx-linux/mlx.h"
# include "./lib/libft/includes/libft.h"

/* ********************************************* */
/* 					STRUCTURES                   */
/* ********************************************* */
typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_game
{
	char	**map;
	void	**imgs;
	void	*mlx;
	void	*mlx_win;
	size_t	nb_move;
	size_t	map_width;
	size_t	map_length;
	size_t	img_width;
	size_t	img_length;
	size_t	nb_items;
	t_pos	start_pos;
	t_pos	exit_pos;
	t_pos	enemy_pos[2];
}	t_game;

/* ********************************************* */
/* 					HELPERS                      */
/* ********************************************* */
/*               	error.c                      */
void	clear_map(char **map);
void	throw_error_errno(void);
void	throw_error_personalized(char *err_msg);
/*					clear.c						 */
int		close_window(t_game *game);
/* ********************************************* */
/* 					PARSING                      */
/* ********************************************* */
/*					parsing.c					 */
t_game	parsing_map(int argc, char **argv);
/*             		utils.c						 */
void	allocate_line(t_game *game, size_t total_line);
size_t	count_line(char *pathname);
t_game	initialize_map(void);
/* 					check_arg.c				 	 */
void	check_arg(int argc, char *argv);
/* 					check_items.c 				 */
void	collect_items(t_game *game);
/* 					read_map.c	 				 */
void	read_map(t_game *game, char *pathname);
/* 					pathfinding.c 			  	 */
void	check_validity_map(t_game *game);
/* ********************************************* */
/* 					GAME                         */
/* ********************************************* */
/* 					render.c	 			  	 */
void	render_img(t_game *game, char el, t_pos pos, int kc);
void	render_map(t_game *game);
void	render_window(t_game *game);
/*					event.c						 */
int		key_hook(int keycode, t_game *game);
void	render_event(t_game *game);
/*					move.c						 */
void	save_player_pos(t_game *game, t_pos *cur_pos, t_pos *new_pos, int mov);
void	update_images(t_game *game, t_pos cur_pos, t_pos new_pos, int keycode);
void	move_player(t_game *game, int mov, int keycode);
/*					enemy.c						 */
void	render_enemy(t_game *game, int n);
void	move_enemies(t_game *game, int keycode);
/*					compare.c					 */	
int		compare_pos(t_pos pos1, t_pos pos2);
void	compare_enemy_player(t_game *game, int n);
int		is_same_enemies(t_game *game, t_pos new_pos, int n);

#endif
