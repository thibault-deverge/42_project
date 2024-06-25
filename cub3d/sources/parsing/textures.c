/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:02:20 by tdeverge          #+#    #+#             */
/*   Updated: 2023/04/18 13:26:59 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*open_texture(t_assets *assets, char **element);

/*
 * @summary:
 * 		- Check validity of line which contains the texture, open this one
 * 		and if it's valid, save its fd into structure assets or throw an 
 * 		error if is a duplicate.
*/
void	save_texture(t_assets *assets, char **element, int id)
{
	char	*path_texture;

	if (element[2] && !ft_is_whitespace(element[2][0]))
	{
		free_parsing(assets, element, NULL);
		exit_error(ERR_TEXT_TYPO, EXIT_ALLOC);
	}
	path_texture = open_texture(assets, element);
	if (path_texture == NULL || assets->textures_path[id])
	{
		free_parsing(assets, element, NULL);
		if (!path_texture)
			exit_error(ERR_TEXT_PATH, EXIT_TEXTURE);
		free(path_texture);
		exit_error(ERR_TEXT_DUP, EXIT_TEXTURE);
	}
	assets->textures_path[id] = path_texture;
}

/*
 * @summary:
 * 		- Remove '\n' at the end of texture if it contains one and check
 * 		if extension of texture is '.xml'. Return an error if not.
 * 		- Open the file if valid and return its fd.
*/
static char	*open_texture(t_assets *assets, char **element)
{
	char	*path;

	if (element[1][ft_strlen(element[1]) - 1] == '\n')
	{
		path = ft_substr(element[1], 0, ft_strlen(element[1]) - 1);
		if (!path)
		{
			free_parsing(assets, element, NULL);
			exit_perror(EXIT_ALLOC);
		}
	}
	else
		path = ft_strdup(element[1]);
	if (!is_extension(path, ".xpm42", 6))
	{
		free_parsing(assets, element, NULL);
		if (path)
			free(path);
		exit_error(ERR_TEXT_TYPO, EXIT_TEXTURE);
	}
	return (path);
}
