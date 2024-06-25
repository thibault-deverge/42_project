/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validity_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 23:58:10 by tdeverge          #+#    #+#             */
/*   Updated: 2023/04/21 16:03:03 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_nb_players(char **map);
static int	check_border(char **map, int x, int y);
static int	is_player(char c);

/*
 * @summary:
 * 		- Check if there is only one player in the map and loop throughout
 * 		the char **map to check if player can't escape.
*/
int	validity_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	if (!check_nb_players(map))
		return (FAIL);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' || is_player_position(map[i][j]))
			{
				if (!check_border(map, i, j))
					return (FAIL);
			}
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

/*
 * @summary:
 * 		- Loop throught the map and increment every time we encounter a
 * 		player. Return an error if there is not exactly one at the end.
*/
static int	check_nb_players(char **map)
{
	int	nb_players;
	int	i;
	int	j;

	i = 0;
	nb_players = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_player(map[i][j]))
				nb_players++;
			j++;
		}
		i++;
	}
	if (nb_players != 1)
	{
		ft_putstr_fd(ERR_MAP_PLAYER, 2);
		return (FAIL);
	}
	return (TRUE);
}

/*
 * @summary:
 * 		- Return an error if player can access one border of the map.
 * 		- Check for every space a player can access if it canno't escape
 * 		from this position, return an error if it can.
*/
static int	check_border(char **map, int x, int y)
{
	int	row;
	int	col;

	row = x - 1;
	col = y - 1;
	if (row < 0 || col < 0)
	{
		ft_putstr_fd(ERR_MAP_BORDER, 2);
		return (FAIL);
	}
	while (row < x + 2)
	{
		col = y - 1;
		while (col < y + 2)
		{
			if (!map[row] || !map[row][col] || map[row][col] == ' ')
			{
				ft_putstr_fd(ERR_MAP_BORDER, 2);
				return (FAIL);
			}
			col++;
		}
		row++;
	}
	return (SUCCESS);
}

static int	is_player(char c)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (TRUE);
	return (FALSE);
}
