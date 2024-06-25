/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 18:44:26 by tdeverge          #+#    #+#             */
/*   Updated: 2022/12/11 16:52:29 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * @summary:
 * 		- Put image to the window at the right position.
*/
static void	put_img_to_win(t_game *game, void *img, int y, int x)
{
	int		pos_y;
	int		pos_x;

	pos_y = (64 * y);
	pos_x = (64 * x) + 64;
	mlx_put_image_to_window(game->mlx, game->mlx_win, img, pos_y, pos_x);
}

/*
 * @summary:
 * 		- load every element on the game structure in a 2d array.
*/
static void	load_images(t_game *game)
{
	void	*mlx;
	int		w;
	int		l;

	w = 64;
	l = 64;
	mlx = game->mlx;
	game->imgs = malloc(sizeof(void *) * (9 + 1));
	if (!game->imgs)
	{
		clear_map(game->map);
		throw_error_errno();
	}
	game->imgs[0] = mlx_xpm_file_to_image(mlx, "./images/tree.xpm", &w, &l);
	game->imgs[1] = mlx_xpm_file_to_image(mlx, "./images/floor.xpm", &w, &l);
	game->imgs[2] = mlx_xpm_file_to_image(mlx, "./images/pikachu.xpm", &w, &l);
	game->imgs[3] = mlx_xpm_file_to_image(mlx, "./images/ash_f.xpm", &w, &l);
	game->imgs[4] = mlx_xpm_file_to_image(mlx, "./images/ash_b.xpm", &w, &l);
	game->imgs[5] = mlx_xpm_file_to_image(mlx, "./images/ash_l.xpm", &w, &l);
	game->imgs[6] = mlx_xpm_file_to_image(mlx, "./images/ash_r.xpm", &w, &l);
	game->imgs[7] = mlx_xpm_file_to_image(mlx, "./images/stairs.xpm", &w, &l);
	game->imgs[8] = mlx_xpm_file_to_image(mlx, "./images/mewtwo.xpm", &w, &l);
	game->imgs[9] = 0;
}

/*
 * @summary:
 * 		- check for which element should be display and
 * 		call the valid function to render with the image.
 * 	@parameters:
 * 		- game : structure of the game.
 * 		- el : element at the position on the map.
 * 		- pos : position of the element we want to represent.
 * 		- kc : keycode of the event.
*/
void	render_img(t_game *game, char el, t_pos pos, int kc)
{
	if (el == '1')
		put_img_to_win(game, game->imgs[0], pos.y, pos.x);
	else if (el == '0')
		put_img_to_win(game, game->imgs[1], pos.y, pos.x);
	else if (el == 'P')
	{
		if (kc == 115 || kc == 65364)
			put_img_to_win(game, game->imgs[3], pos.y, pos.x);
		else if (kc == 119 || kc == 65362)
			put_img_to_win(game, game->imgs[4], pos.y, pos.x);
		else if (kc == 97 || kc == 65361)
			put_img_to_win(game, game->imgs[5], pos.y, pos.x);
		else if (kc == 100 || kc == 65363)
			put_img_to_win(game, game->imgs[6], pos.y, pos.x);
	}
	else if (el == 'C')
		put_img_to_win(game, game->imgs[2], pos.y, pos.x);
	else if (el == 'E')
		put_img_to_win(game, game->imgs[7], pos.y, pos.x);
	else if (el == 'M')
		put_img_to_win(game, game->imgs[8], pos.y, pos.x);
}

/*
 * @summary:
 * 		- render initial map by looping through every element of the map
 * 		and display message to count number of moves.
*/
void	render_map(t_game *game)
{	
	t_pos	pos;
	int		color;
	int		i;
	int		j;

	i = 0;
	j = 0;
	color = 0x00FFFFFF;
	load_images(game);
	while (game->map[i])
	{
		while (game->map[i][j])
		{
			pos.x = i;
			pos.y = j;
			render_img(game, game->map[i][j], pos, 119);
			j++;
		}
		i++;
		j = 0;
	}
	mlx_string_put(game->mlx, game->mlx_win, 32, 42, color, "mouvements: ");
}

/*
 * @summary: 
 * 		- Initialize connexion with mlx and render the map in a window at 
 * 		start of program.
*/
void	render_window(t_game *game)
{
	int		width;
	int		length;

	width = (game->map_width + 1) * 64;
	length = game->map_length * 64;
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, length, width, "Pokemon");
	if (!(game->mlx_win) || !(game->mlx_win))
	{
		clear_map(game->map);
		exit(-1);
	}
}
