/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:01:32 by tdeverge          #+#    #+#             */
/*   Updated: 2023/04/21 16:44:55 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	save_element(t_assets *assets, char **element, char *line);
static char	**safe_split(t_assets *assets, char *str);
static int	find_element_id(char *id_name);
static int	check_all_elements(t_assets *assets, char **element, char *line);

/*
 * @summary: 
 * 		- Loop through the file and split line received. Check which element
 * 		we are analysing and save it if valid. If not valid, it can be the map,
 * 		break the loop and check if all elements were parsed.
 * 		- Return line to parse the map in a next step.
*/
char	*parsing_elements(t_assets *assets)
{
	char	*line;
	char	**element;	

	line = ft_get_line(assets->fd_map);
	element = NULL;
	while (line)
	{
		element = safe_split(assets, line);
		if (is_all_whitespace(element))
		{
			free(line);
			free_matrix(element);
			element = NULL;
			line = ft_get_line(assets->fd_map);
			continue ;
		}
		if (!save_element(assets, element, line))
			break ;
		free_matrix(element);
		element = NULL;
		line = ft_get_line(assets->fd_map);
	}
	check_all_elements(assets, element, line);
	free_matrix(element);
	return (line);
}

static int	save_element(t_assets *assets, char **element, char *line)
{
	int	id;

	id = find_element_id(element[0]);
	if (id == EMPTY_LINE)
	{
		free(line);
		return (EMPTY_LINE);
	}
	if (id >= NORTH_ID && id <= WEST_ID)
	{
		free(line);
		save_texture(assets, element, id);
	}
	else if (id == FLOOR_ID || id == CEIL_ID)
	{
		free(line);
		save_layer(assets, element);
	}
	else
		return (0);
	line = NULL;
	return (1);
}

/*
 * @summary:
 * 		- Simple split over 'str' parameter with protection in case of failure
 * 		of memory allocation with returning an error and exit the program.
*/
static char	**safe_split(t_assets *assets, char *str)
{
	char	**split;

	split = ft_split(str, ' ');
	if (!split)
	{
		free_parsing(assets, NULL, str);
		exit_perror(EXIT_ALLOC);
	}
	return (split);
}

/*
 * @summary:
 * 		- Check if id_name passed as parameter match with one of the arguments
 * 		require and return id of argument if valid to make its identification
 * 		easier later when we save it.
*/
int	find_element_id(char *id_name)
{
	if (!ft_strcmp(id_name, "NO"))
		return (NORTH_ID);
	if (!ft_strcmp(id_name, "EA"))
		return (EAST_ID);
	if (!ft_strcmp(id_name, "SO"))
		return (SOUTH_ID);
	if (!ft_strcmp(id_name, "WE"))
		return (WEST_ID);
	if (!ft_strcmp(id_name, "F"))
		return (FLOOR_ID);
	if (!ft_strcmp(id_name, "C"))
		return (CEIL_ID);
	if (!ft_strcmp(id_name, "\n"))
		return (EMPTY_LINE);
	return (-1);
}

/*
 * @summary:
 * 		-  After parsed all elements, loop through the assets structure and check
 * 		if all elements were parsed and have a value. Return an error if not.
*/
static int	check_all_elements(t_assets *assets, char **element, char *line)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!assets->textures_path[i])
		{
			free_parsing(assets, element, line);
			exit_error(ERR_ELEMENTS, EXIT_ELEMENTS);
		}
		if (i < 3)
		{
			if (assets->floor_rgb[i] == -1 || assets->ceil_rgb[i] == -1)
			{
				free_parsing(assets, element, line);
				exit_error(ERR_ELEMENTS, EXIT_ELEMENTS);
			}
		}
		i++;
	}
	return (TRUE);
}
