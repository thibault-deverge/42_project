/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:01:30 by tdeverge          #+#    #+#             */
/*   Updated: 2023/04/17 17:01:32 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "cub3d.h"

/*					MACROS						*/
# define MINI_W		256
# define MINI_H		256

/*					PROTOTYPES				 	*/
void		draw_minimap(t_render *render);
void		draw_fov(t_render *render, t_rays *rays);
void		draw_player(mlx_image_t *img, t_pt *map);

#endif
