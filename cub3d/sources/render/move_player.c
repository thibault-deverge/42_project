/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 17:24:02 by tdeverge          #+#    #+#             */
/*   Updated: 2023/04/16 18:36:13 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

static void	move_player_front(t_render *render);
static void	move_player_back(t_render *render);
static void	move_player_right(t_render *render);
static void	move_player_left(t_render *render);

/*
 * @summary:
 *		- Checks if a movement key is pressed and performs the corresponding 
 *		action.
 *		- Returns true if movement occurred, false otherwise.
 *		- Movement is performed only if there's no collision with a wall.
*/
bool	check_move(t_render *render)
{
	if (mlx_is_key_down(render->mlx, MLX_KEY_W))
		move_player_front(render);
	else if (mlx_is_key_down(render->mlx, MLX_KEY_A))
		move_player_left(render);
	else if (mlx_is_key_down(render->mlx, MLX_KEY_S))
		move_player_back(render);
	else if (mlx_is_key_down(render->mlx, MLX_KEY_D))
		move_player_right(render);
	else
		return (false);
	return (true);
}

static void	move_player_front(t_render *render)
{
	t_rays		middle_ray;
	t_pt		pos;

	middle_ray = render->rays[WIN_W / 2];
	pos.y = render->player->pos.y + middle_ray.dir.dy * DEP;
	pos.x = render->player->pos.x + middle_ray.dir.dx * DEP;
	if (check_collision(render->map, pos.x, pos.y))
	{
		render->player->pos.x = pos.x;
		render->player->pos.y = pos.y;
	}
}

static void	move_player_back(t_render *render)
{
	t_rays		middle_ray;
	t_pt		pos;

	middle_ray = render->rays[WIN_W / 2];
	pos.y = render->player->pos.y - middle_ray.dir.dy * DEP;
	pos.x = render->player->pos.x - middle_ray.dir.dx * DEP;
	if (check_collision(render->map, pos.x, pos.y))
	{
		render->player->pos.x = pos.x;
		render->player->pos.y = pos.y;
	}
}

static void	move_player_right(t_render *render)
{
	t_rays		middle_ray;
	t_pt		pos;

	middle_ray = render->rays[WIN_W / 2];
	pos.y = render->player->pos.y + middle_ray.dir.dx * DEP;
	pos.x = render->player->pos.x - middle_ray.dir.dy * DEP;
	if (check_collision(render->map, pos.x, pos.y))
	{
		render->player->pos.x = pos.x;
		render->player->pos.y = pos.y;
	}
}

static void	move_player_left(t_render *render)
{
	t_rays		middle_ray;
	t_pt		pos;

	middle_ray = render->rays[WIN_W / 2];
	pos.y = render->player->pos.y - middle_ray.dir.dx * DEP;
	pos.x = render->player->pos.x + middle_ray.dir.dy * DEP;
	if (check_collision(render->map, pos.x, pos.y))
	{
		render->player->pos.x = pos.x;
		render->player->pos.y = pos.y;
	}
}
