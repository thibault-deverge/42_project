/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 15:29:50 by tdeverge          #+#    #+#             */
/*   Updated: 2023/03/08 01:06:15 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static t_rules	*init_rules(void);
static int		fill_rules(t_rules *rules, char *arg, int arg_idx);

/*
 * @summary:
 * 		- Check if number of arguments passed are either 4 or 5. 
 * 		- Check validity of the arguments passed to the program and fill
 * 		structure t_rule if they are valid.
 * 		- Get start_time of the program and write it in t_rule structure.
*/
t_rules	*parser(int argc, char **argv)
{
	t_rules	*rules;
	int		i;

	i = 1;
	if (argc != 5 && argc != 6)
	{
		printf("error: %s", ERROR_ARG_NB);
		return (PARSE_FAILURE);
	}
	rules = init_rules();
	if (!rules)
		return (ALLOC_FAILURE);
	while (argv[i])
	{
		if (!fill_rules(rules, argv[i], i))
		{
			free(rules);
			printf("error: arg%d: %s", i, ERROR_ARG_VALUE);
			return (PARSE_FAILURE);
		}
		i++;
	}
	rules->start_time = get_time(0);
	return (rules);
}

static t_rules	*init_rules(void)
{
	t_rules	*tmp;

	tmp = malloc(sizeof(t_rules));
	if (!tmp)
	{
		printf("error: %s", ERROR_ALLOC);
		return (ALLOC_FAILURE);
	}
	tmp->nb_philos = 0;
	tmp->lifetime = 0;
	tmp->eat_time = 0;
	tmp->sleep_time = 0;
	tmp->total_meals = 0;
	tmp->start_time = 0;
	return (tmp);
}

static int	fill_rules(t_rules *rules, char *arg, int arg_idx)
{
	int	rule;

	rule = ft_atoi_rule(arg);
	if (rule == -1 || ((arg_idx == 1 || arg_idx == 5) && rule == 0))
	{
		printf("error: arg%d: not enough.\n", arg_idx);
		return (PARSE_FAILURE);
	}
	if (arg_idx == 1)
		rules->nb_philos = rule;
	else if (arg_idx == 2)
		rules->lifetime = rule;
	else if (arg_idx == 3)
		rules->eat_time = rule;
	else if (arg_idx == 4)
		rules->sleep_time = rule;
	else
		rules->total_meals = rule;
	return (PARSE_SUCCESS);
}
