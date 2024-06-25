/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:30:18 by tdeverge          #+#    #+#             */
/*   Updated: 2022/12/11 16:51:20 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * @summary:
 * 		- loop through array of images and free them, then free the array.
*/
static void	clear_images(t_game *game)
{
	int	i;

	i = 0;
	while (i < 9)
	{
		mlx_destroy_image(game->mlx, game->imgs[i]);
		game->imgs[i] = NULL;
		i++;
	}
	free(game->imgs);
}

/*
 * @summary:
 * 		- free every memomy in the heap and quit program in a proper way.
*/
int	close_window(t_game *game)
{
	clear_images(game);
	mlx_clear_window(game->mlx, game->mlx_win);
	mlx_destroy_window(game->mlx, game->mlx_win);
	mlx_destroy_display(game->mlx);
	clear_map(game->map);
	free(game->mlx);
	exit(-1);
	return (1);
}
