/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 17:19:34 by tdeverge          #+#    #+#             */
/*   Updated: 2023/04/16 18:07:14 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
 * @summary:
 * 		Check for collision between the player and walls by checking if the
 * 		current position of the player overlaps with any wall tiles in the map.
 *
 * @return: True if there is no collision (i.e. player is not inside a wall),
 * 		   false otherwise (i.e. player's position is inside a wall tile).
*/
bool	check_collision(char **maps, int pos_x, int pos_y)
{
	if (pos_y / TILE_L < 0 || pos_x / TILE_L < 0)
		return (false);
	if (maps[(pos_y + DIAM) / TILE_L][pos_x / TILE_L] == '1')
		return (false);
	if (maps[(pos_y - DIAM) / TILE_L][pos_x / TILE_L] == '1')
		return (false);
	if (maps[pos_y / TILE_L][(pos_x + DIAM) / TILE_L] == '1')
		return (false);
	if (maps[pos_y / TILE_L][(pos_x - DIAM) / TILE_L] == '1')
		return (false);
	if (maps[(pos_y + DIAM) / TILE_L][(pos_x + DIAM) / TILE_L] == '1')
		return (false);
	if (maps[(pos_y - DIAM) / TILE_L][(pos_x - DIAM) / TILE_L] == '1')
		return (false);
	if (maps[(pos_y - DIAM) / TILE_L][(pos_x + DIAM) / TILE_L] == '1')
		return (false);
	if (maps[(pos_y + DIAM) / TILE_L][(pos_x - DIAM) / TILE_L] == '1')
		return (false);
	return (true);
}
