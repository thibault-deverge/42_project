/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_images.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 17:19:56 by tdeverge          #+#    #+#             */
/*   Updated: 2023/04/16 21:34:48 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

/*
 * @summary:
 * 		- Initializes a new image representing the walls and the minimap. 
 * 		- Its height depends on the distance between the player and the '1' tiles.
*/
bool	generate_game_image(t_render *render, bool first_draw)
{
	(void) first_draw;
	render->game_img = mlx_new_image(render->mlx, WIN_W, WIN_H);
	if (!render->game_img)
		return (false);
	if (mlx_image_to_window(render->mlx, render->game_img, 0, 0) < 0)
	{
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
		mlx_close_window(render->mlx);
		return (false);
	}
	build_walls(render, render->player);
	return (true);
}

/*
 * @summary:
 * 		- Creates a new image for the background (floor and sky) and renders 
 * 		it to the window in full screen. This image is only draw once after
 * 		render the window.
*/
bool	generate_background(t_render *render, int floor_color, int ceil_color)
{
	render->back_img = mlx_new_image(render->mlx, WIN_W, WIN_H);
	if (!render->back_img)
	{
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
		mlx_close_window(render->mlx);
		return (false);
	}
	if (mlx_image_to_window(render->mlx, render->back_img, 0, 0) < 0)
	{
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
		mlx_close_window(render->mlx);
		return (false);
	}
	draw_background(render->back_img, floor_color, ceil_color);
	return (true);
}

/*
 * @summary:
 * 		- Check initial coordinates and make the player face the valid
 * 		orientation.
 * 		- This function only operate the first time generate_images() is
 * 		called.
*/
void	make_first_rotation_player(t_render *render)
{
	if (is_player_position(render->player->orientation))
	{
		if (render->player->orientation == 'W')
			rotation(render, WEST_DIR);
		if (render->player->orientation == 'S')
			rotation(render, SOUTH_DIR);
		if (render->player->orientation == 'E')
			rotation(render, EAST_DIR);
	}
}
