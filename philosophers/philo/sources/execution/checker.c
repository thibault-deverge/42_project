/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 22:55:52 by tdeverge          #+#    #+#             */
/*   Updated: 2023/03/08 15:57:03 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/*
 * @summary:
 * 		- Check if every philosophers eat at leat the must_eat arg number
 * 		of meal and break the loop if its the case (dinner is finish).
*/
int	break_end_dinner(t_mutexes *mutexes, int nb_philos)
{
	int	end_flag;

	end_flag = 0;
	pthread_mutex_lock(&mutexes->meal_lock);
	if (mutexes->end_counter == nb_philos)
		end_flag = 1;
	pthread_mutex_unlock(&mutexes->meal_lock);
	return (end_flag);
}

/*
 * @summary:
 * 		- Check if number of meals philosopher must eat was passed as
 * 		parameter (optional argument).
 * 		- If argument was passed, check if the philosopher passed as parameter
 * 		ate all meals an return a boolean value.
 * 		- If argument was not passed, return truthy value to continue dinner.
*/
void	check_meals(t_philosopher *philo)
{
	int				total_meals;

	total_meals = philo->rules->total_meals;
	pthread_mutex_lock(&philo->mutexes->meal_lock);
	if (total_meals && philo->meals_eaten == total_meals)
		philo->mutexes->end_counter++;
	pthread_mutex_unlock(&philo->mutexes->meal_lock);
}

/*
 * @summary:
 * 		- Check if a philosopher died and return a boolean value.
*/
int	check_death(t_mutexes *mut)
{
	int	is_death;

	is_death = 0;
	pthread_mutex_lock(&mut->death_lock);
	if (mut->death_flag == 1)
		is_death = 1;
	pthread_mutex_unlock(&mut->death_lock);
	return (is_death);
}
