/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:20:09 by tdeverge          #+#    #+#             */
/*   Updated: 2023/03/08 00:30:56 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	init_supervisor_value(t_supervisor *supervisor, t_data *data);
static void	wait_philos(t_philosopher *philos, int nb_philos);

/*
 * @summary:
 * 		- Create a structure, fill it with informations need to check
 * 		death of a philosopher and launch it as a thread.
*/
t_supervisor	*launch_supervisor(t_data *data)
{
	t_supervisor	*spv;

	spv = malloc(sizeof(t_supervisor));
	if (!spv)
	{
		printf("error: %s", ERROR_ALLOC);
		return (ALLOC_FAILURE);
	}
	init_supervisor_value(spv, data);
	pthread_create(&spv->th_id, 0, routine_supervisor, (void *)(spv));
	return (spv);
}

/*
 * @summary:
 * 		- Loop over philos array and initiate a thread for each of them.
 * 		- Wait for the threads to finishes before exiting the function.
*/
void	launch_philos(t_philosopher *philos, int nb_philos)
{
	pthread_t	*thread_id;
	int			i;

	i = 0;
	while (i < nb_philos)
	{
		thread_id = &philos[i].th_id;
		pthread_create(thread_id, 0, routine_philo, (void *)(&philos[i]));
		i++;
	}
	wait_philos(philos, nb_philos);
}

static void	init_supervisor_value(t_supervisor *supervisor, t_data *data)
{
	supervisor->mutexes = data->mutexes;
	supervisor->philos = data->philos;
	supervisor->nb_philos = data->rules->nb_philos;
	supervisor->start_time = data->rules->start_time;
	supervisor->lifetime = data->rules->lifetime;
	supervisor->total_meals = data->rules->total_meals;
}

static void	wait_philos(t_philosopher *philos, int nb_philos)
{
	int	i;

	i = 0;
	while (i < nb_philos)
	{
		pthread_join(philos[i].th_id, 0);
		i++;
	}
}
