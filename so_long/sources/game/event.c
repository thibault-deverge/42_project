/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 18:21:16 by tdeverge          #+#    #+#             */
/*   Updated: 2022/12/11 16:52:09 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * @summary:
 * 		- listen for keyboard press and redirect to the valid function
 * 		depend which keycode.
 * @parameters:
 * 		- keycode : keyboard touch press to start event.
 * 		- game : structure of the game.
*/
int	key_hook(int keycode, t_game *game)
{
	if (keycode == 65307)
		close_window(game);
	if (keycode == 119 || keycode == 65362)
		move_player(game, 1, keycode);
	if (keycode == 100 || keycode == 65363)
		move_player(game, 2, keycode);
	if (keycode == 115 || keycode == 65364)
		move_player(game, 3, keycode);
	if (keycode == 97 || keycode == 65361)
		move_player(game, 4, keycode);
	return (1);
}

/*
 * @summary:
 * 		- create event when cross to close is clicked and when keyboard
 * 		touch is triggered.
*/
void	render_event(t_game *game)
{
	mlx_hook(game->mlx_win, 17, 1L << 17, close_window, game);
	mlx_key_hook(game->mlx_win, key_hook, game);
}
