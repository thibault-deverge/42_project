/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fov_minimap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 17:22:32 by tdeverge          #+#    #+#             */
/*   Updated: 2023/04/16 18:10:09 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d_bonus.h"

static t_pt	add_dir_at_pos(t_pt pos, t_vector dir);

/*
 * @summary:
 *		- This function draws the field of view (FOV) on the minimap.
 *		- It iterates through each horizontal pixel and calculates the FOV,
 *        then displays it on the minimap if the distance is within 100 pixels
 *        from the player.
*/
void	draw_fov(t_render *render, t_rays *rays)
{
	t_player	*player;
	t_pt		pos;
	t_pt		rend_pos;
	int			i;

	i = 0;
	player = render->player;
	while (i < WIN_W)
	{
		pos.x = player->pos.x + rays[i].dir.dx + 0.5 * get_sign(rays[i].dir.dx);
		pos.y = player->pos.y + rays[i].dir.dy + 0.5 * get_sign(rays[i].dir.dy);
		rend_pos.x = (MINI_W / 2) + rays[i].dir.dx;
		rend_pos.y = (MINI_H / 2) + rays[i].dir.dy;
		while (render->map[(int)pos.y / TILE_L][(int)pos.x / TILE_L] != '1')
		{
			if (get_distance(player->pos.x, player->pos.y, pos.x, pos.y) <= 100)
				mlx_put_pixel(render->game_img, rend_pos.x, rend_pos.y, GRAY);
			pos.x = pos.x + rays[i].dir.dx;
			if (render->map[(int)pos.y / TILE_L][(int)pos.x / TILE_L] == '1')
				break ;
			pos.y = pos.y + rays[i].dir.dy;
			rend_pos = add_dir_at_pos(rend_pos, rays[i].dir);
		}
		i++;
	}
}

static t_pt	add_dir_at_pos(t_pt pos, t_vector dir)
{
	pos.x = pos.x + dir.dx;
	pos.y = pos.y + dir.dy;
	return (pos);
}
