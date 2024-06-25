/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 20:56:05 by tdeverge          #+#    #+#             */
/*   Updated: 2023/03/12 18:25:17 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	single_philo(t_philosopher *philo);
static void	eat_spaghettis(t_philosopher *philo);
static void	lock_forks(t_philosopher *philo);
static void	print_action(t_philosopher *philo, int action);

/*
 * @summary:
 * 		- Loop on a eat->sleep->think cycle until it finishes all meals or
 * 		one philosopher die.
 * 		- Once it all meals are eaten, increment a flag to notify the 
 * 		philosopher finish its dinner and exit the function.
*/
void	*routine_philo(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->id % 2)
		usleep(500);
	while (!check_death(philo->mutexes))
	{
		if (break_end_dinner(philo->mutexes, philo->rules->nb_philos))
			break ;
		if (philo->rules->nb_philos == 1)
			single_philo(philo);
		else
		{
			eat_spaghettis(philo);
			check_meals(philo);
			print_action(philo, SLEEP);
			usleep_safe(philo, philo->rules->sleep_time);
			print_action(philo, THINK);
		}
	}
	return (0);
}

static void	single_philo(t_philosopher *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, FORK);
	usleep_safe(philo, philo->rules->lifetime);
	pthread_mutex_unlock(philo->left_fork);
}

static void	eat_spaghettis(t_philosopher *philo)
{
	lock_forks(philo);
	pthread_mutex_lock(&philo->mutexes->meal_lock);
	philo->last_meal_time = get_time(philo->rules->start_time);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->mutexes->meal_lock);
	print_action(philo, EAT);
	usleep_safe(philo, philo->rules->eat_time);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	lock_forks(t_philosopher *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_action(philo, FORK);
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, FORK);
}

static void	print_action(t_philosopher *philo, int action)
{
	long int	start_time;
	int			id;

	id = philo->id;
	start_time = philo->rules->start_time;
	pthread_mutex_lock(&philo->mutexes->print_lock);
	if (!philo->mutexes->print_flag)
	{
		if (action == FORK)
			printf("%s%ld %d has taken a fork\n",
				BLUE, get_time(start_time), id);
		if (action == EAT)
			printf("%s%ld %d is eating\n", CYAN, get_time(start_time), id);
		if (action == SLEEP)
			printf("%s%ld %d is sleeping\n", GREEN, get_time(start_time), id);
		if (action == THINK)
			printf("%s%ld %d is thinking\n", PURPLE, get_time(start_time), id);
		printf("%s", BLACK);
	}
	pthread_mutex_unlock(&philo->mutexes->print_lock);
}
