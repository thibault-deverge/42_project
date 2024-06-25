/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 20:21:39 by tdeverge          #+#    #+#             */
/*   Updated: 2023/03/07 23:58:30 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static pthread_mutex_t	*init_forks(int nb_philos);

/*
 * @summary:
 *		- Initialise a stuct of type mutexes which contains mutexes for
 *		the philosopher dinners.
 *		- Initialise an array of mutexes for the forks and init them.
 *		- Initialise a mutex to print on stdout.
*/
t_mutexes	*init_mutexes(int nb_philos)
{
	t_mutexes	*mutexes;

	mutexes = malloc(sizeof(t_mutexes));
	if (!mutexes)
	{
		printf("error: %s", ERROR_ALLOC);
		return (ALLOC_FAILURE);
	}
	mutexes->forks = init_forks(nb_philos);
	if (!mutexes->forks)
		return (ALLOC_FAILURE);
	pthread_mutex_init(&mutexes->print_lock, NULL);
	pthread_mutex_init(&mutexes->meal_lock, NULL);
	pthread_mutex_init(&mutexes->death_lock, NULL);
	mutexes->end_counter = 0;
	mutexes->print_flag = 0;
	mutexes->death_flag = 0;
	return (mutexes);
}

static pthread_mutex_t	*init_forks(int nb_philos)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * nb_philos);
	if (!forks)
	{
		printf("error: %s", ERROR_ALLOC);
		return (ALLOC_FAILURE);
	}
	while (i < nb_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}
