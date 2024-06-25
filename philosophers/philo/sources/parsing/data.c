/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:05:45 by tdeverge          #+#    #+#             */
/*   Updated: 2023/03/07 17:20:55 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/*
 * @summary:
 * 		- Parse arguments of the programs and intialize all elements needed
 * 		to do the dining philosopher problems in three distincts structures.
 * 		Fill the structure with these sub-structure and return it.
*/
t_data	*init_data(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (ALLOC_FAILURE);
	data->rules = parser(argc, argv);
	if (!data->rules)
	{
		free(data);
		return (PARSE_FAILURE);
	}
	data->mutexes = init_mutexes(data->rules->nb_philos);
	if (!data->mutexes)
	{
		free(data->rules);
		free(data);
		return (ALLOC_FAILURE);
	}
	data->philos = init_philos(data->rules, data->mutexes);
	if (!data->philos)
	{
		free_all(data, NULL);
		return (ALLOC_FAILURE);
	}
	return (data);
}
