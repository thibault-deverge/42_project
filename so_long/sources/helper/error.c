/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 21:45:00 by tdeverge          #+#    #+#             */
/*   Updated: 2022/12/11 16:51:29 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	clear_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	else
	{
		while (map[i])
		{
			free(map[i]);
			i++;
		}
		free(map);
	}
}

void	throw_error_errno(void)
{
	perror("Error");
	exit(-1);
}

void	throw_error_personalized(char *err_msg)
{
	ft_printf("Error:\n\t%s\n", err_msg);
	exit(-1);
}
