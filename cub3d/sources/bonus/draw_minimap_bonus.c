/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 17:22:43 by tdeverge          #+#    #+#             */
/*   Updated: 2023/04/17 09:54:55 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d_bonus.h"

static t_pt	incremente_position(float x, float y);
static void	init_minimap(t_render *render);
static void	draw_wall_2d(t_render *render, t_pt player, t_pt pos, t_pt draw);

/*
 * @summary: 
 * 		- Draws a minimap around the player, centered on its position, 
 * 		showing the map tiles within a 9x9 square around the player.
 *		- For each tile in the minimap, the function checks the corresponding 
 *		element in the game map and draws the corresponding color to the 
 *		minimap pixel.
 */
void	draw_minimap(t_render *render)
{
	t_pt	player;
	t_pt	pos;
	t_pt	draw;

	init_minimap(render);
	player.x = render->player->pos.x - 4 * TILE_L;
	player.y = render->player->pos.y - 4 * TILE_L;
	pos = incremente_position(player.x, player.y);
	player.x += pos.x;
	player.y += pos.y;
	while (render->map[(int)player.y / TILE_L]
		&& player.y < render->player->pos.y + 4 * TILE_L)
	{
		draw.x = pos.x;
		player.x = render->player->pos.x - 4 * TILE_L + pos.x;
		draw_wall_2d(render, player, pos, draw);
		player.y++;
		pos.y++;
	}
}

static void	init_minimap(t_render *render)
{
	int	x;
	int	y;

	y = 0;
	while (y < MINI_H)
	{
		x = 0;
		while (x < MINI_W)
		{
			mlx_put_pixel(render->game_img, x, y, BLACK);
			x++;
		}
		y++;
	}
}

static void	draw_wall_2d(t_render *render, t_pt player, t_pt pos, t_pt draw)
{
	float	x_end;

	x_end = render->player->pos.x + 4 * TILE_L;
	while (player.x < x_end
		&& render->map[(int)player.y / TILE_L][(int)player.x / TILE_L])
	{
		if (render->map[(int)player.y / TILE_L][(int)player.x / TILE_L] == '1')
			mlx_put_pixel(render->game_img, draw.x, pos.y, WHITE);
		draw.x++;
		player.x++;
	}
}

static t_pt	incremente_position(float x, float y)
{
	int		value;
	t_pt	point;

	value = 0;
	while (x < 0)
	{
		value++;
		x++;
	}
	point.x = value;
	value = 0;
	while (y < 0)
	{
		value++;
		y++;
	}
	point.y = value;
	return (point);
}
