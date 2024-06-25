/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:07:43 by tdeverge          #+#    #+#             */
/*   Updated: 2023/03/08 15:01:14 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int argc, char **argv)
{
	t_supervisor	*supervisor;
	t_data			*data;

	data = init_data(argc, argv);
	if (!data)
		return (EXIT_FAILURE);
	supervisor = launch_supervisor(data);
	if (!supervisor)
	{
		free_all(data, supervisor);
		return (EXIT_FAILURE);
	}
	launch_philos(data->philos, data->rules->nb_philos);
	pthread_join(supervisor->th_id, 0);
	free_all(data, supervisor);
	return (EXIT_SUCCESS);
}
