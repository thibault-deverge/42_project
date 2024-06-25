/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 00:02:50 by tdeverge          #+#    #+#             */
/*   Updated: 2023/04/21 16:04:16 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
 * @summary:
 * 		- Check if argument passed to the program is a file of type 'cub' and
 * 		open it.
 * 		- Parse elements, map and check validity of the map (border, doable...).
*/
void	parsing(t_assets *assets, char *assets_path)
{
	char	*line;

	line = NULL;
	if (!is_extension(assets_path, ".cub", 4))
		exit_error(ERR_CUB, EXIT_EXTENSION);
	assets->fd_map = open(assets_path, O_RDONLY);
	if (assets->fd_map == -1)
		exit_perror(EXIT_ARG);
	line = parsing_elements(assets);
	parsing_map(assets, line);
	close(assets->fd_map);
	if (!assets->map)
	{
		ft_putstr_fd(ERR_MAP_LOST, 2);
		free_assets(assets);
		exit(EXIT_MAP);
	}
	if (!validity_map(assets->map))
	{
		free_assets(assets);
		exit(EXIT_MAP);
	}
	get_layer_hexadecimal(assets, assets->floor_rgb, assets->ceil_rgb);
}
