/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_supervisor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 00:00:39 by tdeverge          #+#    #+#             */
/*   Updated: 2023/03/08 15:48:30 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	is_lifetime_over(t_supervisor *spv, int i);
static void	kill_philo(t_mutexes *mutexes, long int start_time, int idx_philo);
static int	is_end_dinner(t_mutexes *mutexes, int nb_philos);

/*
 * @summary:
 * 		- Loop until is end of dinner (if optional argument exists) or until
 * 		a philosopher die.
 * 		- Loop over philosophers consantly and check if their lifetime since
 * 		last meal is passed. If its the case, kill philosopher, notify via
 * 		a flag someone was being killed and exit thread.
*/
void	*routine_supervisor(void *arg)
{
	t_supervisor	*spv;
	int				i;

	i = 0;
	spv = (t_supervisor *)arg;
	while (!is_end_dinner(spv->mutexes, spv->nb_philos))
	{
		while (i < spv->nb_philos)
		{
			if (is_lifetime_over(spv, i))
			{
				kill_philo(spv->mutexes, spv->start_time, i + 1);
				return (0);
			}
			i++;
		}
		i = 0;
	}
	return (0);
}

static int	is_lifetime_over(t_supervisor *spv, int i)
{
	long int	time_since_meal;

	pthread_mutex_lock(&spv->mutexes->meal_lock);
	time_since_meal = get_time(spv->start_time);
	time_since_meal -= spv->philos[i].last_meal_time;
	pthread_mutex_unlock(&spv->mutexes->meal_lock);
	if (time_since_meal >= spv->lifetime)
		return (1);
	return (0);
}

static void	kill_philo(t_mutexes *mutexes, long int start_time, int idx_philo)
{
	pthread_mutex_lock(&mutexes->death_lock);
	mutexes->death_flag = 1;
	pthread_mutex_unlock(&mutexes->death_lock);
	pthread_mutex_lock(&mutexes->print_lock);
	mutexes->print_flag = 1;
	printf("%s%ld %d died%s\n", RED, get_time(start_time), idx_philo, BLACK);
	pthread_mutex_unlock(&mutexes->print_lock);
}

static int	is_end_dinner(t_mutexes *mutexes, int nb_philos)
{
	int	end_flag;

	end_flag = 0;
	pthread_mutex_lock(&mutexes->meal_lock);
	if (mutexes->end_counter == nb_philos)
	{
		pthread_mutex_lock(&mutexes->print_lock);
		mutexes->print_flag = 1;
		pthread_mutex_unlock(&mutexes->print_lock);
		end_flag = 1;
	}
	pthread_mutex_unlock(&mutexes->meal_lock);
	return (end_flag);
}
