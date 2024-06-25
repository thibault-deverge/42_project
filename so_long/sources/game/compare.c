/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 16:56:16 by tdeverge          #+#    #+#             */
/*   Updated: 2022/12/11 16:51:45 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * @summary:
 * 		- Compare two position and return 1 if equal or 0 otherwise.
*/
int	compare_pos(t_pos pos1, t_pos pos2)
{
	if (pos1.x == pos2.x && pos1.y == pos2.y)
		return (1);
	return (0);
}

/*
 * @summary:
 * 		- End game if enemy touch the player on the map.
 * @parameters:
 * 		- game : structure of the game
 * 		- n : index of the enemy compared with the player
*/
void	compare_enemy_player(t_game *game, int n)
{
	if (game->enemy_pos[n].x == game->start_pos.x
		&& game->enemy_pos[n].y == game->start_pos.y)
	{
		close_window(game);
	}
}

/*
 * @summary:
 * 		- Check if enemy next move will be on same position of the other
 * 		enemy. Return 1 if it's the case or 0 otherwise.
*/
int	is_same_enemies(t_game *game, t_pos new_pos, int n)
{
	int	i;

	if (n == 0)
		i = 1;
	else
		i = 0;
	if (new_pos.x == game->enemy_pos[i].x && new_pos.y == game->enemy_pos[i].y)
		return (1);
	return (0);
}
