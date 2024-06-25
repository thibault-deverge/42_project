/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 17:23:49 by tdeverge          #+#    #+#             */
/*   Updated: 2023/04/21 18:55:15 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

/*
 * @summary:
 *      - Function that is called repeatedly as a loop to update the screen.
 *      - Checks for any key presses and calls the corresponding functions 
 *      (move, rotate, etc.).
 *      - If an action was taken, the images (except background) are re-rendered
 *      to reflect the player's field of view.
*/
void	loop_hook(void *arg)
{
	t_render	*render;

	render = arg;
	if (mlx_is_key_down(render->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(render->mlx);
	if (!check_move(render) && !check_rotation(render))
		return ;
	mlx_delete_image(render->mlx, render->game_img);
	if (!generate_game_image(render, false))
		mlx_close_window(render->mlx);
	build_walls(render, render->player);
}
