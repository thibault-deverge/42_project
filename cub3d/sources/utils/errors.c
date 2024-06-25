/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 17:06:44 by tdeverge          #+#    #+#             */
/*   Updated: 2023/04/16 19:58:00 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	exit_program(t_render *render, t_assets *assets)
{
	if (assets)
		free_assets(assets);
	free_textures(render);
	if (render->rays)
		free(render->rays);
	if (render->mlx)
		mlx_terminate(render->mlx);
	exit(EXIT_GAME);
}

void	exit_error(char *err_msg, int status)
{
	ft_putstr_fd(err_msg, 2);
	exit(status);
}

void	exit_perror(int exit_status)
{
	perror("error");
	exit(exit_status);
}
