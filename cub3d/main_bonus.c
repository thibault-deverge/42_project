/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 17:16:29 by tdeverge          #+#    #+#             */
/*   Updated: 2023/04/16 20:07:52 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d_bonus.h"

int	main(int argc, char **argv)
{
	t_assets	assets;
	t_render	render;
	t_player	player;

	if (argc != 2)
		exit_error(ERR_ARG, EXIT_ARG);
	init_assets(&assets);
	parsing(&assets, argv[1]);
	init_render(&render, &player, assets.map);
	if (!init_img_textures(&render, &assets))
		exit_program(&render, &assets);
	if (!render_window(&render, &assets))
		exit_program(&render, &assets);
	mlx_loop_hook(render.mlx, loop_hook, &render);
	mlx_loop(render.mlx);
	exit_program(&render, &assets);
	return (EXIT_SUCCESS);
}
