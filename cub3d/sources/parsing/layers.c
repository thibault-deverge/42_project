/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:01:57 by tdeverge          #+#    #+#             */
/*   Updated: 2023/04/17 15:05:03 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	save_color(t_assets *assets, char **element, int color, int idx);
static void	check_comma(t_assets *assets, char **element, char *cur_pos);
static void	check_format(t_assets *assets, char **element, char *cur_pos);
static int	atoi_rgb(t_assets *assets, char **element, char *str);

/*
 * @summary:
 * 		- Loop over the three colors of the rgb and save it into asset's
 * 		structure. Return an error if line is not what is expected.
*/
void	save_layer(t_assets *assets, char **element)
{
	int	color;
	int	rgb_idx;
	int	i;

	i = 0;
	rgb_idx = 0;
	while (rgb_idx < 3)
	{
		color = atoi_rgb(assets, element, &element[1][i]);
		while (ft_isdigit(element[1][i]))
			i++;
		if (rgb_idx < 2)
		{
			check_comma(assets, element, &element[1][i]);
			i++;
		}
		save_color(assets, element, color, rgb_idx);
		rgb_idx++;
	}
	check_format(assets, element, &element[1][i]);
}

/*
 * @summary: 
 * 		- Check which layer we are saving (floor or ceil) and if it was not
 * 		already parsed before. If it was, return an error or save it into
 * 		assets structure.
*/
static void	save_color(t_assets *assets, char **element, int color, int idx)
{
	if (!ft_strcmp(element[0], "F"))
	{
		if (assets->floor_rgb[idx] != -1)
		{
			free_parsing(assets, element, NULL);
			exit_error(ERR_LAYER_DUP, EXIT_LAYER);
		}
		assets->floor_rgb[idx] = color;
	}
	if (!ft_strcmp(element[0], "C"))
	{
		if (assets->ceil_rgb[idx] != -1)
		{
			free_parsing(assets, element, NULL);
			exit_error(ERR_LAYER_DUP, EXIT_LAYER);
		}
		assets->ceil_rgb[idx] = color;
	}
}

/*
 * @summary:
 * 		- Check if the current position of the string contains a comma and 
 * 		the next character is a digit (allow to return an error if another
 * 		comma follow a first one).
*/
static void	check_comma(t_assets *assets, char **element, char *cur_pos)
{
	if (cur_pos[0] != ',' || !ft_isdigit(cur_pos[1]))
	{
		free_parsing(assets, element, NULL);
		exit_error(ERR_LAYER_NB, EXIT_LAYER);
	}
}

/*
 * @summary:
 * 		- Check format of layer's line and return an error if something follow
 * 		the rgb colors.
*/
static void	check_format(t_assets *assets, char **element, char *cur_pos)
{
	int	i;
	int	j;

	i = 0;
	j = 2;
	while (element[j])
	{
		if (!ft_is_all_whitespace(element[j]))
		{
			free_parsing(assets, element, NULL);
			exit_error(ERR_LAYER_NB, EXIT_LAYER);
		}
		j++;
	}
	while (cur_pos[i])
	{
		if (cur_pos[i] && !ft_is_whitespace(cur_pos[i]))
		{
			free_parsing(assets, element, NULL);
			exit_error(ERR_LAYER_RGB, EXIT_LAYER);
		}
		i++;
	}
}

/*
 * @summary:
 * 		- ft_atoi modified to check if sum is a valid rgb number.
 * 		- Return an error if it's not in range [0-255] or if there 
 * 		is no digits.
*/
static int	atoi_rgb(t_assets *assets, char **element, char *str)
{
	int	sum;
	int	i;

	i = 0;
	sum = 0;
	if (!ft_isdigit(str[i]))
	{
		free_parsing(assets, element, NULL);
		exit_error(ERR_LAYER_RGB, EXIT_LAYER);
	}
	while (ft_isdigit(str[i]))
	{
		sum = (sum * 10) + (str[i] - '0');
		i++;
	}
	if (sum < 0 || sum > 255)
	{
		free_parsing(assets, element, NULL);
		exit_error(ERR_LAYER_RGB, EXIT_LAYER);
	}
	return (sum);
}
