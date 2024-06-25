/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 17:19:10 by tdeverge          #+#    #+#             */
/*   Updated: 2023/04/16 18:39:42 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d_bonus.h"

/*
 * @summary:
 * 		- Initialize the player and rays, create a window and render the initial
 * 		background and images.
*/
bool	render_window(t_render *render, t_assets *assets)
{
	if (!init_rays(render))
		return (false);
	init_player(render);
	render->mlx = mlx_init(WIN_W, WIN_H, "cub3d", true);
	if (!render->mlx)
	{
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
		return (false);
	}
	if (!generate_background(render, assets->floor_hexa, assets->ceil_hexa))
		return (false);
	if (!generate_game_image(render, true))
		return (false);
	draw_fov(render, render->rays);
	return (true);
}
