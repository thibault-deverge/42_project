/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 15:54:16 by tdeverge          #+#    #+#             */
/*   Updated: 2022/12/11 16:49:29 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * @summary:
 * 		- return a duplicate of the map to then use flood fill algorithm
 * 		on it.
*/
static char	**duplicate_map(t_game *game)
{
	char	**map_dup;
	int		i;
	int		j;

	i = 0;
	j = 0;
	map_dup = ft_calloc(sizeof(char *), game->map_width + 1);
	if (!map_dup)
	{
		clear_map(game->map);
		throw_error_errno();
	}
	while (game->map[i])
	{
		map_dup[i] = ft_strdup(game->map[i]);
		if (!map_dup[i])
		{
			clear_map(map_dup);
			clear_map(game->map);
			throw_error_personalized(MEM_ERR);
		}
		i++;
	}
	return (map_dup);
}

/*
 * @summary: 
 * 		- use recursion and DFS to find if path is valid.
 * 		- will flood the map the player can reach with char 'D'
 * 		to every position reachable by the player.
*/
static void	flood_fill(t_game *game, char **map, int x, int y)
{
	if (map[x][y] == '1' || map[x][y] == 'D')
		return ;
	map[x][y] = 'D';
	flood_fill(game, map, x + 1, y);
	flood_fill(game, map, x - 1, y);
	flood_fill(game, map, x, y + 1);
	flood_fill(game, map, x, y - 1);
}

/*
 * @summary:
 * 		- check if exit and all collectibles are reachables by the
 * 		player on a map.
*/
static int	is_valid_path(char **map)
{
	char	cur_pos;
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (map[x])
	{
		while (map[x][y])
		{
			cur_pos = map[x][y];
			if (cur_pos == 'C' || cur_pos == 'E' || cur_pos == 'P')
				return (0);
			y++;
		}
		x++;
		y = 0;
	}
	return (1);
}

/*
 * @summary: 
 * 		- check if the player is able to take all collectibles and
 * 		reach the exit on a map.
*/
void	check_validity_map(t_game *game)
{
	char	**map_dup;
	int		start_x;
	int		start_y;

	start_x = game->start_pos.x;
	start_y = game->start_pos.y;
	map_dup = duplicate_map(game);
	flood_fill(game, map_dup, start_x, start_y);
	if (!is_valid_path(map_dup))
	{
		clear_map(map_dup);
		clear_map(game->map);
		throw_error_personalized(WRONG_PATH);
		exit(-1);
	}
	clear_map(map_dup);
}
