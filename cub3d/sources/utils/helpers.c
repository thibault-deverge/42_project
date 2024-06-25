/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 17:07:06 by tdeverge          #+#    #+#             */
/*   Updated: 2023/04/16 17:07:08 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

bool	is_player_position(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (true);
	return (false);
}

float	get_distance(float x1, float y1, float x2, float y2)
{
	return (sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
}

float	get_sign(int vector)
{
	if (vector < 0)
		return (-1);
	return (1);
}
