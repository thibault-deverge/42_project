/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 17:06:28 by tdeverge          #+#    #+#             */
/*   Updated: 2023/04/18 13:36:43 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

/*
 * @summary:
 * 		- Initialize assets structure with -1 value. That will allow
 * 		to check during parsing if we have duplicate element by checking
 * 		it it was already parsed.
*/
void	init_assets(t_assets *assets)
{
	int	i;

	i = 0;
	assets->map = NULL;
	while (i < 4)
	{
		assets->textures_path[i] = NULL;
		if (i < 3)
		{
			assets->floor_rgb[i] = -1;
			assets->ceil_rgb[i] = -1;
		}
		i++;
	}
	assets->floor_hexa = 0;
	assets->ceil_hexa = 0;
}

/*
 * @summary:
 * 		- Loop throught the map until finding the player and
 * 		init its structure with his position in pixels, its position
 * 		in minimap (center) and the letter which define its initial
 * 		orientation.
*/
void	init_player(t_render *render)
{
	char		**map;
	int			x;
	int			y;

	y = 0;
	map = render->map;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (is_player_position(map[y][x]))
			{
				render->player->pos.y = y * TILE_L + TILE_L / 2;
				render->player->pos.x = x * TILE_L + TILE_L / 2;
				render->player->orientation = map[y][x];
				make_first_rotation_player(render);
				return ;
			}
			x++;
		}
		y++;
	}
}

/*
 * @summary:
 * 		- Initialize structure array at beginning of program with map and
 * 		player structure.
 * 		- Initialize mlx and rays to NULL at first (error handle later).
*/
void	init_render(t_render *render, t_player *player, char **map)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		render->textures[i].colors = NULL;
		render->textures[i].width = 0;
		render->textures[i].height = 0;
		i++;
	}
	render->map = map;
	render->mlx = NULL;
	render->player = player;
	render->rays = NULL;
}

/*
 * @summary:
 * 		- Initialize an array of structure 'rays' of the window width
 * 		size. Save direction and angle for each rays.
*/
t_rays	*init_rays(t_render *render)
{
	int			i;

	i = 0;
	render->rays = malloc(sizeof(t_rays) * WIN_W);
	if (!render->rays)
	{
		perror("error");
		return (NULL);
	}
	while (i < WIN_W)
	{
		render->rays[i].dir.dy = NORTH_DIR;
		render->rays[i].dir.dx = ((i - (WIN_W / 2)) * ((M_PI / 3) / WIN_W));
		render->rays[i].angle = ((i - (WIN_W / 2)) * ((M_PI / 3) / WIN_W));
		render->rays[i].length = 0;
		i++;
	}
	return (render->rays);
}

/*
 * @summary:
 * 		- Initializes textures to draw on the wall. First load them then convert
 * 		theirs pixels (each for one color) to a int ** matrix where first dimension
 * 		will be height of the texture and each row a line of the texture.
 * 		- Each line will contains an int for every pixels with all colors in a 
 * 		hexadecimal form.
*/
bool	init_img_textures(t_render *render, t_assets *assets)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		render->textures_mlx[i] = mlx_load_xpm42(assets->textures_path[i]);
		if (!render->textures_mlx[i])
		{
			ft_putstr_fd(ERR_TEXT_LOAD, 2);
			return (false);
		}
		if (!convert_textures(render, i))
		{
			perror("error");
			return (false);
		}
		mlx_delete_texture((void *)render->textures_mlx[i]);
		i++;
	}
	return (true);
}
