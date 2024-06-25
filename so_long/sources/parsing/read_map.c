/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 23:50:07 by tdeverge          #+#    #+#             */
/*   Updated: 2022/12/11 16:50:39 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	is_wall_surrounded(t_game *game)
{
	size_t	i;

	i = 0;
	while (i < game->map_length)
	{
		if (game->map[0][i] != '1' || game->map[game->map_width - 1][i] != '1')
		{
			clear_map(game->map);
			throw_error_personalized(NO_WALLS);
		}
		i++;
	}
	i = 0;
	while (i < game->map_width)
	{
		if (game->map[i][0] != '1' || game->map[i][game->map_length - 1] != '1')
		{
			clear_map(game->map);
			throw_error_personalized(NO_WALLS);
		}
		i++;
	}
}

static void	is_rectangle(t_game *game)
{
	size_t	len;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	game->map_length = ft_strlen(game->map[0]);
	while (game->map[i])
	{
		len = ft_strlen(game->map[i]);
		if (len != game->map_length)
		{
			clear_map(game->map);
			throw_error_personalized(NO_RECTANGLE);
		}
		i++;
	}
	if (game->map_width < 3 || game->map_length < 3)
	{
		clear_map(game->map);
		throw_error_personalized(TOO_SMALL);
	}
}

static void	is_valid_symbol(t_game *game)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	while (game->map[i])
	{
		while (game->map[i][j])
		{
			c = game->map[i][j];
			if (c != '0' && c != '1' && c != 'C' && c != 'E' && c != 'P')
			{
				clear_map(game->map);
				throw_error_personalized(WRONG_SYMBOLS);
			}
			j++;
		}
		i++;
		j = 0;
	}
}

/*
 * @summary:
 * 		- read a line of the map file and return it
*/
static char	*read_line(int fd)
{
	char	*line;
	int		line_len;
	int		i;

	i = 0;
	line = get_next_line(fd);
	if (!line)
		return (NULL);
	line_len = ft_strlen(line);
	if (line[line_len - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	else
		line[line_len] = '\0';
	return (line);
}

/*
 * @summary:
 * 		- read trough the map file and save it as a map in the
 * 		game structure.
 * 		- check if map is rectangle, only contains valid symbols and is 
 * 		surrounded by walls.
*/
void	read_map(t_game *game, char *pathname)
{
	size_t	total_line;
	size_t	idx_line;
	char	*line;
	int		fd;

	idx_line = 0;
	total_line = count_line(pathname);
	allocate_line(game, total_line);
	fd = open(pathname, O_RDONLY);
	if (fd == -1)
		throw_error_errno();
	while (idx_line < total_line)
	{
		line = read_line(fd);
		if (!line)
			break ;
		game->map[idx_line] = line;
		idx_line++;
	}
	game->map[total_line] = 0;
	is_rectangle(game);
	is_wall_surrounded(game);
	is_valid_symbol(game);
}
