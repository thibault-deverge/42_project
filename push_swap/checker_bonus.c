/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 14:45:52 by tdeverge          #+#    #+#             */
/*   Updated: 2023/01/09 14:13:10 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	main(int argc, char **argv)
{
	t_stack		stack;

	init_stack(&stack);
	parsing_args(&stack, argc, argv);
	check_duplicate(&stack);
	read_operations(&stack);
	checker_is_sorted(&stack);
	free_stacks(&stack);
	return (0);
}
