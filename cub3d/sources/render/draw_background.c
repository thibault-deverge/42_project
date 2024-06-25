/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 17:20:25 by tdeverge          #+#    #+#             */
/*   Updated: 2023/04/16 18:09:48 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
 * @summary:
 * 		- Draws the background of the game window, with the top half as the sky
 * 		and the bottom half as the floor.
 */
void	draw_background(mlx_image_t *img, int floor_color, int ceil_color)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_H / 2)
	{
		x = 0;
		while (x < WIN_W)
		{
			mlx_put_pixel(img, x, y, ceil_color);
			x++;
		}
		y++;
	}
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			mlx_put_pixel(img, x, y, floor_color);
			x++;
		}
		y++;
	}
}
