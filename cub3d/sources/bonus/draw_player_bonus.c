/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 17:23:05 by tdeverge          #+#    #+#             */
/*   Updated: 2023/04/16 18:21:07 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d_bonus.h"

static int	get_circle_px(int x1, int y1, int x2, int y2);

/*
 * @summary:
 * 		- Renders a player on the minimap as a circle in the center, 
 * 		corresponding to a quarter of a tile.
 *		- The player is drawn to the image using RED pixel color.
 *		- The function uses the get_circle_px() helper function to compute the
 *		distance between the current pixel and the center of the player circle,
 *		and draws a pixel if the distance is within a quarter of a tile.
*/
void	draw_player(mlx_image_t *img, t_pt *map)
{
	t_pt	coord;
	int		distance;
	int		i;
	int		j;

	i = 0;
	coord.x = MINI_W / 2;
	coord.y = MINI_H / 2;
	while (i < TILE_L)
	{
		j = 0;
		while (j < TILE_L)
		{
			distance = get_circle_px(coord.x, coord.y, map->x + j, map->y + i);
			if (distance <= DIAM)
				mlx_put_pixel(img, map->x + j, map->y + i, RED);
			j++;
		}
		i++;
	}
}

/*
 * @summary:
 * 		-Helper function to calculate the distance between two points in a plane 
 * 		using the Pythagorean theorem.
 */
static int	get_circle_px(int x1, int y1, int x2, int y2)
{
	return (sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2)));
}
