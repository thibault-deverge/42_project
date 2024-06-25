/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 23:38:30 by tdeverge          #+#    #+#             */
/*   Updated: 2022/12/11 16:50:51 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * @summary:
 * 		- Initialize the game structure with default value and return it.
*/
t_game	initialize_map(void)
{
	t_game	game;

	game.map = NULL;
	game.imgs = 0;
	game.mlx = 0;
	game.mlx_win = 0;
	game.map_width = 0;
	game.map_length = 0;
	game.img_width = 0;
	game.img_length = 0;
	game.nb_move = 0;
	game.nb_items = 0;
	game.start_pos.x = 0;
	game.start_pos.y = 0;
	game.exit_pos.x = 0;
	game.exit_pos.y = 0;
	game.enemy_pos[0].x = 0;
	game.enemy_pos[0].y = 0;
	game.enemy_pos[1].x = 0;
	game.enemy_pos[1].y = 0;
	return (game);
}

/*
 * @summary:
 * 		- Allocate first dimension of the map which is the number
 * 		of line (width)
*/
void	allocate_line(t_game *game, size_t total_line)
{
	game->map_width = total_line;
	game->map = malloc(sizeof(char *) * (total_line + 1));
	if (!(game->map))
		throw_error_errno();
}

/*
 * @summary:
 * 		- open map file and read through it to count the number
 * 		of lines it contains.
*/
size_t	count_line(char *pathname)
{
	size_t	line_count;
	int		fd;
	char	*line;

	line_count = 0;
	fd = open(pathname, O_RDONLY);
	if (fd == -1)
		throw_error_errno();
	while (1)
	{
		line = get_next_line(fd);
		if (!line && line_count == 0)
			throw_error_personalized(EMPTY_MAP);
		if (!line)
		{
			close(fd);
			return (line_count);
		}
		line_count++;
		free(line);
		line = 0;
	}
}
