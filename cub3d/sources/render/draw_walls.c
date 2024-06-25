/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 17:23:17 by tdeverge          #+#    #+#             */
/*   Updated: 2023/04/16 18:52:59 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

static void		draw_wall(t_render *render, int i);
static void		initial_incrementation(t_render *render, t_pt *pos, int i);
static float	get_wall_height(t_rays ray);
static void		draw_big_wall(t_render *render, int i, float wall_height);

/*
* @summary:
* 		- Loop through each horizontal pixel and calculate the distance
* 		between the wall and the player. 
* 		- Once we have the distance, send it to function 'draw_wall' to 
* 		calculate its height and draw it on this pixel.
*/
void	build_walls(t_render *render, t_player *player)
{
	t_rays		*rays;
	t_pt		pos;
	int			i;

	i = 0;
	rays = render->rays;
	while (i < WIN_W)
	{
		initial_incrementation(render, &pos, i);
		while (render->map[(int)pos.y / TILE_L][(int)pos.x / TILE_L] != '1')
		{
			pos.x += rays[i].dir.dx / 3;
			rays[i].flag = HORIZONTAL;
			if (render->map[(int)pos.y / TILE_L][(int)pos.x / TILE_L] == '1')
				break ;
			pos.y += rays[i].dir.dy / 3;
			rays[i].flag = VERTICAL;
		}
		rays[i].collision = pos;
		rays[i].length = get_distance(player->pos.x,
				player->pos.y, pos.x, pos.y);
		draw_wall(render, i);
		i++;
	}
}

/*
 * @summary:
 * 		- Calculate height of the wall and draw it to the screen. Send it
 * 		to draw_big_wall() if its size is bigger than the window height.
 * 		- Draw line by line, using the textures to get color of the pixel.
*/
static void	draw_wall(t_render *render, int i)
{
	t_wall		wall;
	t_pixel		texture;
	int			color;
	int			pixel;

	wall.height = get_wall_height(render->rays[i]);
	if (wall.height > WIN_H)
	{
		draw_big_wall(render, i, wall.height);
		return ;
	}
	wall.start_draw = WIN_H / 2 - wall.height / 2;
	wall.end_draw = WIN_H / 2 + wall.height / 2;
	pixel = 0;
	texture = get_pixel_param(render, render->rays[i], wall.height);
	while (wall.start_draw < wall.end_draw)
	{
		color = get_texture(texture, pixel);
		mlx_put_pixel(render->game_img, i, wall.start_draw, color);
		wall.start_draw++;
		pixel++;
	}
}

/*
 * @summary:
 * 		- Function responsible for drawing walls that are taller than
 * 		the window height.
*/
static void	draw_big_wall(t_render *render, int i, float wall_height)
{
	float		start_draw;
	int			color;
	int			pixel;
	t_pixel		texture;

	start_draw = WIN_H / 2 - wall_height / 2;
	pixel = 0;
	while (start_draw < 0)
	{
		start_draw++;
		pixel++;
	}
	texture = get_pixel_param(render, render->rays[i], wall_height);
	while (start_draw < WIN_H)
	{
		color = get_texture(texture, pixel);
		mlx_put_pixel(render->game_img, i, start_draw, color);
		start_draw++;
		pixel++;
	}
}

static void	initial_incrementation(t_render *render, t_pt *pos, int i)
{
	t_rays	*rays;

	rays = render->rays;
	pos->x = render->player->pos.x;
	pos->y = render->player->pos.y;
	pos->x += rays[i].dir.dx + 0.5 * get_sign(rays[i].dir.dx);
	rays[i].flag = HORIZONTAL;
	if (render->map[(int)pos->y / TILE_L][(int)pos->x / TILE_L] != '1')
	{
		pos->y += rays[i].dir.dy + 0.5 * get_sign(rays[i].dir.dy);
		rays[i].flag = VERTICAL;
	}
}

static float	get_wall_height(t_rays ray)
{
	float	height;
	float	win_w;
	float	win_h;

	win_w = (float)WIN_W;
	win_h = (float)WIN_H;
	height = WIN_H / (ray.length * cos(ray.angle)) * (TILE_L * (win_w / win_h));
	return (height);
}
