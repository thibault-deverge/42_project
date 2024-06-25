/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 15:23:12 by tdeverge          #+#    #+#             */
/*   Updated: 2023/03/12 18:24:14 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/*
 * @summary:
 * 		- Get timestamp and substract timestant of the program when
 * 		it starts to have current timestamp.
 * 		- Return current_time of the program as a long integer.
*/
long int	get_time(long int start_time)
{
	struct timeval	time;
	long int		current_time;

	gettimeofday(&time, NULL);
	current_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	current_time -= start_time;
	return (current_time);
}

/*
 * @summary:
 * 		- Do fractional sleep in a loop in case one philosopher die 
 * 		to stop the simulation.
*/
void	usleep_safe(t_philosopher *philo, int sleep_time)
{
	if (philo->rules->lifetime < sleep_time)
		usleep(philo->rules->lifetime * 1000);
	else
		usleep(sleep_time * 1000);
}
