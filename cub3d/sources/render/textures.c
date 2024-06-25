/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 17:24:33 by tdeverge          #+#    #+#             */
/*   Updated: 2023/04/16 18:45:39 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

static t_text	get_pos_texture(t_render *render, t_rays ray);

/*
 * @summary:
 * 		- Calculate the pixel position on the texture, the corresponding
 * 		column, and the step based on the height of the wall.
*/
t_pixel	get_pixel_param(t_render *render, t_rays ray, float wall_height)
{
	t_pixel	pixel;
	float	pixel_pos;

	pixel.texture = get_pos_texture(render, ray);
	if (ray.flag == VERTICAL)
		pixel_pos = ray.collision.x;
	else
		pixel_pos = ray.collision.y;
	while (pixel_pos >= 32.0)
		pixel_pos -= 32.0;
	pixel.column = (pixel_pos * pixel.texture.width) / 32.0;
	pixel.step = pixel.texture.height / wall_height;
	return (pixel);
}

/*
 * @summary:
 * 		- Get the texture color for the corresponding position and step.
 * 		- Return the color value for the texture at the given position and step.
*/
int	get_texture(t_pixel pixel, int position)
{
	float	i;

	i = pixel.step * position;
	return (pixel.texture.colors[(int)i][(int)pixel.column]);
}

/*
 * @summary:
 * 		- Get the corresponding texture to the ray intersection point.
 */
static t_text	get_pos_texture(t_render *render, t_rays ray)
{
	if (ray.flag == VERTICAL && ray.dir.dy < 0)
		return (render->textures[0]);
	else if (ray.flag == VERTICAL && ray.dir.dy > 0)
		return (render->textures[2]);
	else if (ray.flag == HORIZONTAL && ray.dir.dx < 0)
		return (render->textures[3]);
	else
		return (render->textures[1]);
}
