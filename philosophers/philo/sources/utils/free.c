/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:28:36 by tdeverge          #+#    #+#             */
/*   Updated: 2023/03/07 23:59:46 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	destroy_mutexes(t_mutexes *mutexes, int nb_philos);

/*
 * @summary:
 * 		- free all memory dynamically allocated and destroy mutexes to have
 * 		a proper exit.
*/
void	free_all(t_data *data, t_supervisor *supervisor)
{
	int	i;

	i = 0;
	if (data->mutexes)
	{
		destroy_mutexes(data->mutexes, data->rules->nb_philos);
		free(data->mutexes);
	}
	if (data->philos)
	{
		while (i < data->rules->nb_philos)
		{
			if (data->philos + i)
				free(data->philos[i].rules);
			i++;
		}
		free(data->philos);
	}
	if (data->rules)
		free(data->rules);
	if (supervisor)
		free(supervisor);
	free(data);
}

static void	destroy_mutexes(t_mutexes *mutexes, int nb_philos)
{
	int	i;

	i = 0;
	while (i < nb_philos)
	{
		pthread_mutex_destroy(&mutexes->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&mutexes->print_lock);
	pthread_mutex_destroy(&mutexes->meal_lock);
	pthread_mutex_destroy(&mutexes->death_lock);
	free(mutexes->forks);
}
