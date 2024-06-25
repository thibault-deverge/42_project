/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 12:49:24 by tdeverge          #+#    #+#             */
/*   Updated: 2022/12/11 16:50:21 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * @summary:
 * 		- main function of parsing who call sub-function for parsing.
*/
t_game	parsing_map(int argc, char **argv)
{
	t_game	game;

	game = initialize_map();
	check_arg(argc, argv[1]);
	read_map(&game, argv[1]);
	collect_items(&game);
	check_validity_map(&game);
	return (game);
}
