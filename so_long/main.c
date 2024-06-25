/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 22:45:12 by tdeverge          #+#    #+#             */
/*   Updated: 2022/12/07 17:03:03 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"
#include <time.h>

int	main(int argc, char **argv)
{
	t_game	game;

	srand(time(0));
	game = parsing_map(argc, argv);
	render_enemy(&game, 0);
	render_enemy(&game, 1);
	render_window(&game);
	render_map(&game);
	render_event(&game);
	mlx_loop(game.mlx);
	close_window(&game);
	return (0);
}
