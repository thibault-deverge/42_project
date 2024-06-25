/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 17:00:33 by tdeverge          #+#    #+#             */
/*   Updated: 2022/12/11 16:51:58 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * @summary:
 * 		- Generate random number from 0 to n - 1.
*/
static int	generate_random_num(int n)
{
	int	i;

	i = (rand() % n);
	return (i);
}

/*
 * @summary:
 * 		- Generate random movement for enemy and save his current and next
 * 		destination in cur_pos and next_pos.
 * @parameters:
 * 		- game: structure of the game
 * 		- cur_pos: enemy actual position
 * 		- new_pos: enemy next destination
 * 		- n : index of the enemy
*/
static void	save_enemy_pos(t_game *game, t_pos *cur_pos, t_pos *new_pos, int n)
{
	int	mov;

	mov = generate_random_num(5);
	cur_pos->x = game->enemy_pos[n].x;
	cur_pos->y = game->enemy_pos[n].y;
	new_pos->x = game->enemy_pos[n].x;
	new_pos->y = game->enemy_pos[n].y;
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
 * @summary: 
 * 		- Calcul and check if new position of the enemy is valid, and update
 * 		if it's the case.
 * @parameters:
 * 		- game: structure of the game
 * 		- keycode: keyboard touch pressed to start the movement
 * 		- n : index of the enemy updated
*/
static void	update_enemy(t_game *game, int keycode, int n)
{
	t_pos	cur_pos;
	t_pos	new_pos;
	int		same_enemies;

	save_enemy_pos(game, &cur_pos, &new_pos, n);
	same_enemies = is_same_enemies(game, new_pos, n);
	if (game->map[new_pos.x][new_pos.y] == '0' && !same_enemies)
	{
		game->enemy_pos[n].x = new_pos.x;
		game->enemy_pos[n].y = new_pos.y;
		render_img(game, '0', cur_pos, keycode);
		render_img(game, 'M', game->enemy_pos[n], keycode);
	}
	compare_enemy_player(game, n);
}

/*
 * @summary:
 * 		- start random movements for ennemies everytime player
 * 		move if map is big enough
*/
void	move_enemies(t_game *game, int keycode)
{	
	if (game->map_length < 6 || game->map_width < 6)
		return ;
	update_enemy(game, keycode, 0);
	update_enemy(game, keycode, 1);
}

/*
 * @summary:
 * 		- Initialize two random ennemies if map is larger enough.
 * 		- Render these enemies to the map and save it in the game 
 * 		structure
 * @parameters:
 * 		- game : structure of the game
 * 		- n : index of the enemy
*/
void	render_enemy(t_game *game, int n)
{
	int	rand_x;
	int	rand_y;
	int	i;

	if (game->map_length < 6 || game->map_width < 6)
		return ;
	rand_x = 0;
	rand_y = 0;
	i = 0;
	while (game->map[rand_x][rand_y] != '0')
	{
		rand_x = generate_random_num(game->map_width);
		rand_y = generate_random_num(game->map_length);
		if (i == 100)
			return ;
	}
	game->enemy_pos[n].x = rand_x;
	game->enemy_pos[n].y = rand_y;
	game->map[rand_x][rand_y] = 'M';
}
