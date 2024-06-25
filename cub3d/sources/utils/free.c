/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 17:06:56 by tdeverge          #+#    #+#             */
/*   Updated: 2023/04/21 18:47:49 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

/*
 * @summary:
 * 		- Free matrix passed as parameter by looping through it.
*/
void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

/*
 * @summary:
 * 		- Loop through all the texture first, then loop through
 * 		the int ** containing the color and free the matrix.
*/
void	free_textures(t_render *render)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 4)
	{
		j = 0;
		while (render->textures[i].colors && j < render->textures[i].height)
		{
			if (render->textures[i].colors[j])
				free(render->textures[i].colors[j]);
			j++;
		}
		if (render->textures[i].colors)
			free(render->textures[i].colors);
		i++;
	}
}

/*
 * @summary:
 * 		- Check if map exists and free its matrix.
 * 		- Check if textures are open and close them.
*/
void	free_assets(t_assets *assets)
{
	int	i;

	i = 0;
	if (assets->map)
		free_matrix(assets->map);
	while (i < 4)
	{
		if (assets->textures_path[i])
			free(assets->textures_path[i]);
		i++;
	}
}

/*
 * @summary:
 * 		- Free all memory allocate during parsing (assets and line got
 * 		via get_line function).
*/
void	free_parsing(t_assets *assets, char **split_line, char *line)
{
	if (assets->fd_map >= 0)
		close(assets->fd_map);
	if (split_line)
	{
		free_matrix(split_line);
		split_line = NULL;
	}
	if (line)
	{
		free(line);
		line = NULL;
	}
	free_assets(assets);
}
