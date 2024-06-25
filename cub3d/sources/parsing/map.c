/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 23:54:43 by tdeverge          #+#    #+#             */
/*   Updated: 2023/04/24 15:08:54 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_line(t_assets *assets, char *line);
static void	insert_line(t_assets *assets, char *line);
static int	is_valid_char(char c);

/*
 * @summary:
 * 		- Loop through the map and check if line is valid then insert it
 * 		to matrice 'map' in assets structure.
 * 		- If there is a newline, break the loop and continue to loop to
 * 		see if there is another element. If yes, return an error because
 * 		map should be last element of the file.
*/
void	parsing_map(t_assets *assets, char *line)
{
	while (line)
	{
		if (!check_line(assets, line))
		{
			line = ft_get_line(assets->fd_map);
			break ;
		}
		insert_line(assets, line);
		line = ft_get_line(assets->fd_map);
	}
	while (line && line[0] == '\n')
	{
		free(line);
		line = ft_get_line(assets->fd_map);
	}
	if (line)
	{
		free_parsing(assets, NULL, line);
		exit_error(ERR_MAP_DATA, EXIT_MAP);
	}
}

/*
 * @summary:
 * 		- Check line of the map to see if it contains only valid characters
 * 		or return an error. Also check if line is empty which mean parsing
 * 		of the map is done.
*/
static int	check_line(t_assets *assets, char *line)
{
	int	i;

	i = 0;
	if (line[i] == '\n')
	{
		free(line);
		line = NULL;
		return (0);
	}
	while (line[i])
	{
		if (!is_valid_char(line[i]))
		{
			free_parsing(assets, NULL, line);
			exit_error(ERR_MAP_CHAR, EXIT_MAP);
		}
		i++;
	}
	return (1);
}

/*
 * @summary:
 * 		- Make a substring of the map line without '\n' at the end
 * 		and insert it into the matrix map.
*/
static void	insert_line(t_assets *assets, char *line)
{
	int		i;

	i = ft_strlen(line) - 1;
	if (line[i] == '\n')
		line[i] = 0;
	assets->map = ft_insert_matrix(assets->map, line);
	if (!assets->map)
	{
		free_parsing(assets, NULL, line);
		exit_perror(EXIT_ALLOC);
	}
	free(line);
	line = NULL;
}

/*
 * @summary:
 * 		- Return TRUE (1) if the character received as parameter is an accepted
 * 		character in the map or FALSE (0) otherwise.
*/
static int	is_valid_char(char c)
{
	if (c == '0' || c == '1' || c == ' ' || c == 'N'
		|| c == 'S' || c == 'W' || c == 'E' || c == '\n')
		return (TRUE);
	return (FALSE);
}
