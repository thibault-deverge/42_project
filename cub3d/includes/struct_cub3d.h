/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_cub3d.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 17:26:53 by tdeverge          #+#    #+#             */
/*   Updated: 2023/04/16 17:57:42 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef STRUCT_CUB3D_H
# define STRUCT_CUB3D_H

typedef struct s_assets {
	char	**map;
	char	*textures_path[4];
	int		floor_rgb[3];
	int		ceil_rgb[3];
	int		floor_hexa;
	int		ceil_hexa;
	int		fd_map;
}	t_assets;

typedef struct s_vector {
	float	dx;
	float	dy;
}	t_vector;

typedef struct s_point {
	int	x;
	int	y;
}	t_point;

typedef struct s_pt {
	float	x;
	float	y;
}	t_pt;

typedef struct s_player {
	t_pt		pos;
	char		orientation;
}	t_player;

typedef struct s_rays {
	t_vector	dir;
	float		angle;
	float		length;
	int			flag;
	t_pt		collision;
}	t_rays;

typedef struct s_text {
	int	**colors;
	int	width;
	int	height;
}	t_text;

typedef struct s_pixel {
	float	step;
	float	column;
	t_text	texture;
}	t_pixel;

typedef struct s_wall {
	float	height;
	float	start_draw;
	float	end_draw;
}	t_wall;

typedef struct s_render {
	char		**map;
	mlx_t		*mlx;
	xpm_t		*textures_mlx[4];
	t_text		textures[4];
	mlx_image_t	*back_img;
	mlx_image_t	*game_img;
	t_player	*player;
	t_rays		*rays;
}	t_render;

#endif
