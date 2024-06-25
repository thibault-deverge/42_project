/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_items.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:23:34 by tdeverge          #+#    #+#             */
/*   Updated: 2022/12/11 16:50:10 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * @summary:
 * 		- Check if map contains exactly 1 start and exit position and at least
 * 		1 collectible. Throw an error if not.
*/
static void	check_components(t_game *game, size_t nb_start, size_t nb_end)
{
	if (game->nb_items < 1)
	{
		clear_map(game->map);
		throw_error_personalized(COLL_ERR);
	}
	else if (nb_start != 1)
	{
		clear_map(game->map);
		throw_error_personalized(PLAYER_ERR);
	}
	else if (nb_end != 1)
	{
		clear_map(game->map);
		throw_error_personalized(EXIT_ERR);
	}
}

/*
 * @summary:
 * 		- add start/exit position at game structure or increment number
 * 		of collectibles.
 * @return:
 * 		- 1 if start/exit position to increment counter in call function.
 * 		- 0 if collectible.
*/
static size_t	add_item(t_game *game, char item, int x, int y)
{
	if (item == 'C')
	{
		game->nb_items++;
		return (0);
	}
	else if (item == 'P')
	{
		game->start_pos.x = x;
		game->start_pos.y = y;
		return (1);
	}
	else if (item == 'E')
	{
		game->exit_pos.x = x;
		game->exit_pos.y = y;
		return (1);
	}
	return (0);
}

/*
 * @summary:
 * 		- Check start/exit position are correct and save their position.
 * 		- Count number of collectibles.
*/
void	collect_items(t_game *game)
{
	size_t	nb_start;
	size_t	nb_exit;
	size_t	x;
	size_t	y;

	nb_start = 0;
	nb_exit = 0;
	x = 0;
	y = 0;
	while (x < game->map_width)
	{
		while (y < game->map_length)
		{
			if (game->map[x][y] == 'C')
				add_item(game, game->map[x][y], x, y);
			else if (game->map[x][y] == 'P')
				nb_start += add_item(game, game->map[x][y], x, y);
			else if (game->map[x][y] == 'E')
				nb_exit += add_item(game, game->map[x][y], x, y);
			y++;
		}
		y = 0;
		x++;
	}
	check_components(game, nb_start, nb_exit);
}
