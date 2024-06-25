/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 17:24:14 by tdeverge          #+#    #+#             */
/*   Updated: 2023/04/16 18:41:23 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

/*
 * @summary:
 * 		- Check which key was pressed and send it to the rotation function if 
 * 		it's a horizontal arrow key.
 * 		- Rotate the player using trigonometry and PI value.
*/
bool	check_rotation(t_render *render)
{
	if (mlx_is_key_down(render->mlx, MLX_KEY_RIGHT))
		rotation(render, -90);
	else if (mlx_is_key_down(render->mlx, MLX_KEY_LEFT))
		rotation(render, 90);
	else
		return (false);
	return (true);
}

/*
 * @summary:
 * 		- Rotate the player's field of view by modifying the rays' direction
 * 		vectors.
 * 		- Trigonometry is used to calculate the new vectors based on the angle
 * 		value (in degrees).
*/
void	rotation(t_render *render, int angle)
{
	t_rays	*rays;
	float	tmp;
	int		i;

	i = 0;
	rays = render->rays;
	while (i < WIN_W)
	{
		tmp = rays[i].dir.dx;
		rays[i].dir.dx = rays[i].dir.dx * cos(M_PI / angle)
			+ rays[i].dir.dy * sin(M_PI / angle);
		rays[i].dir.dy = rays[i].dir.dy * cos(M_PI / angle)
			- tmp * sin(M_PI / angle);
		i++;
	}
}
