/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 18:25:10 by tdeverge          #+#    #+#             */
/*   Updated: 2022/12/11 16:52:18 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * @summary:
 * 		- Save player's current position, calcul it's next position and
 * 		save it into structure passed as parameter.
 * @parameter:
 * 		- game : structure of the game.
 * 		- cur_pos : current position of player.
 * 		- new_pos : next position of player.
 * 		- mov : integer from 1 to 4 which represent next movement
 * 		in a clockwise order.
*/
void	save_player_pos(t_game *game, t_pos *cur_pos, t_pos *new_pos, int mov)
{
	cur_pos->x = game->start_pos.x;
	cur_pos->y = game->start_pos.y;
	new_pos->x = game->start_pos.x;
	new_pos->y = game->start_pos.y;
	if (mov == 1)
		new_pos->x--;
	else if (mov == 2)
		new_pos->y++;
	else if (mov == 3)
		new_pos->x++;
	else if (mov == 4)
		new_pos->y--;
}

/*
 * @summary :
 * 		- Update window and display counter of moves every time player
 * 		change it's position.
*/
void	update_images(t_game *game, t_pos cur_pos, t_pos new_pos, int keycode)
{
	char	*last_mov;
	char	*mov_str;
	int		color_white;
	int		color_black;

	last_mov = ft_itoa(game->nb_move - 1);
	mov_str = ft_itoa(game->nb_move);
	color_white = 0x00FFFFFF;
	color_black = 0x00000000;
	mlx_string_put(game->mlx, game->mlx_win, 110, 43, color_black, last_mov);
	render_img(game, 'P', new_pos, keycode);
	if (game->exit_pos.x == cur_pos.x && game->exit_pos.y == cur_pos.y)
		render_img(game, 'E', cur_pos, keycode);
	else if (compare_pos(game->enemy_pos[0], cur_pos))
		render_img(game, 'M', cur_pos, keycode);
	else if (compare_pos(game->enemy_pos[1], cur_pos))
		render_img(game, 'M', cur_pos, keycode);
	else
		render_img(game, '0', cur_pos, keycode);
	mlx_string_put(game->mlx, game->mlx_win, 110, 43, color_white, mov_str);
	free(mov_str);
	free(last_mov);
	mov_str = NULL;
	last_mov = NULL;
}

/*
 * @summary:
 * 		- Move player to a destination depend which keycode is 
 * 		used and what is element contains the destination.
 * 		- Check where the player is going and update 'game' 
 * 		structure in consequence.
 * @parameters:
 * 		- mov : integer from 1 to 4 who save the direction of the 
 * 		move in a clockwise order.
 * 		- keycode : keyboard touch pressed to start the event.
*/
void	move_player(t_game *game, int mov, int keycode)
{
	t_pos			cur_pos;
	t_pos			new_pos;

	save_player_pos(game, &cur_pos, &new_pos, mov);
	move_enemies(game, keycode);
	if (game->map[new_pos.x][new_pos.y] == '1')
		return ;
	if (game->map[new_pos.x][new_pos.y] == 'C')
	{
		game->nb_items--;
		game->map[new_pos.x][new_pos.y] = '0';
	}
	if (game->map[new_pos.x][new_pos.y] == 'E')
	{
		if (game->nb_items == 0)
		{
			ft_printf("END (%d move)\n", game->nb_move);
			close_window(game);
		}
	}
	game->start_pos = new_pos;
	game->nb_move++;
	update_images(game, cur_pos, new_pos, keycode);
}
