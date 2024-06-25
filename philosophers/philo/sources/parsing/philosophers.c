/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 20:21:12 by tdeverge          #+#    #+#             */
/*   Updated: 2023/03/08 15:07:26 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static t_philosopher	*allocate_philos(int nb_philos);
static t_rules			*duplicate_rules(t_rules *rules);
static void				*ft_calloc(size_t nmemb, size_t size);

/*
 * @summary:
 * 		- Initialise an arrays of philosophers and fill them with valid
 * 		informations.
 * 		- Add a references to mutexes array and a reference to fork at their
 * 		left and right.
 * 		- Add a duplicate of the rule structure to it.
*/
t_philosopher	*init_philos(t_rules *rules, t_mutexes *mutexes)
{
	t_philosopher	*philos;
	int				i;

	i = 0;
	philos = allocate_philos(rules->nb_philos);
	if (!philos)
		return (ALLOC_FAILURE);
	while (i < rules->nb_philos)
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		if (i == 0)
			philos[i].left_fork = &mutexes->forks[rules->nb_philos - 1];
		else
			philos[i].left_fork = &mutexes->forks[i - 1];
		philos[i].right_fork = &mutexes->forks[i];
		philos[i].mutexes = mutexes;
		philos[i].rules = duplicate_rules(rules);
		if (!philos[i].rules)
			return (ALLOC_FAILURE);
		i++;
	}
	return (philos);
}

static t_philosopher	*allocate_philos(int nb_philos)
{
	t_philosopher	*philos;

	philos = ft_calloc(sizeof(t_philosopher), nb_philos);
	if (!philos)
	{
		printf("error: %s", ERROR_ALLOC);
		return (ALLOC_FAILURE);
	}
	return (philos);
}

static t_rules	*duplicate_rules(t_rules *rules)
{
	t_rules	*rules_dup;

	rules_dup = malloc(sizeof(t_rules));
	if (!rules_dup)
	{
		printf("error: %s", ERROR_ALLOC);
		return (ALLOC_FAILURE);
	}
	rules_dup->nb_philos = rules->nb_philos;
	rules_dup->lifetime = rules->lifetime;
	rules_dup->eat_time = rules->eat_time;
	rules_dup->sleep_time = rules->sleep_time;
	rules_dup->total_meals = rules->total_meals;
	rules_dup->start_time = rules->start_time;
	return (rules_dup);
}

static void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	void	*pt_memory;

	if (nmemb * size > INT_MAX || size > INT_MAX)
		return (NULL);
	pt_memory = malloc(nmemb * size);
	if (pt_memory)
	{
		i = 0;
		while (i < nmemb * size)
		{
			((char *)pt_memory)[i] = 0;
			i++;
		}
		return (pt_memory);
	}
	else
		return (NULL);
}
