/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:01:43 by tdeverge          #+#    #+#             */
/*   Updated: 2023/04/17 20:26:39 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_all_whitespace(char **element)
{
	int	i;
	int	j;

	i = 0;
	while (element[i])
	{
		j = 0;
		while (element[i][j])
		{
			if (!ft_is_whitespace(element[i][j]))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

/*
 * @summary:
 * 		- Check first if path is not an hidden file with its length and if it
 * 		matches with the extension passed as parameter. 
 * 		- Finally check it's not a hidden file into a directory if a path is given.
*/
int	is_extension(char *path, char *extension, int length)
{
	int	i;

	i = ft_strlen(path) - length;
	if (i <= 0 || ft_strncmp(&path[i], extension, 4) || path[i - 1] == '/')
		return (FALSE);
	return (TRUE);
}

/*
 * @summary:
 * 		- Tahe rgb value get in parsing and convert it to hexadecimal value in
 * 		the form of an int. Save it into assets structure.
*/
void	get_layer_hexadecimal(t_assets *assets, int *floor, int *ceil)
{
	int	floor_hexa;
	int	ceil_hexa;

	floor_hexa = get_hexa(floor[0], floor[1], floor[2], 255);
	ceil_hexa = get_hexa(ceil[0], ceil[1], ceil[2], 255);
	assets->floor_hexa = floor_hexa;
	assets->ceil_hexa = ceil_hexa;
}

int	get_hexa(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}
