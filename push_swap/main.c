/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 11:18:43 by tdeverge          #+#    #+#             */
/*   Updated: 2022/12/29 00:28:32 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	stack;

	init_stack(&stack);
	parsing_args(&stack, argc, argv);
	check_duplicate(&stack);
	normalize_values(&stack);
	sort_inputs(&stack);
	free_stacks(&stack);
	return (0);
}
