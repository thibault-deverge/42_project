/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_inputs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 00:20:13 by tdeverge          #+#    #+#             */
/*   Updated: 2022/12/30 22:35:21 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
 * @summary:
 * 		- Bring back to stack A the element when its target element and handle
 * 		case when smaller elements are already been brought back.
*/
static void	handle_target(t_stack *stack, int *target)
{
	if (stack->head_b->index == *target)
	{
		push_a(stack, 1);
		if (stack->head_a->index > stack->head_a->next->index)
		{
			swap_a(stack, 1);
			(*target)--;
		}
		if (stack->tail_a->index == stack->head_a->index - 1)
		{
			r_rotate_a(stack, 1);
			(*target)--;
		}
		else if (stack->head_a->index > stack->tail_a->index)
			r_rotate_a(stack, 1);
		(*target)--;
	}
}

/*
 * @summary:
 * 		- Bring back elements sorted via the pivot to Stack A from the
 * 		larger to smaller one.
 * 		- Bring it back also if head is target element - 1 and -2 to optimize
 * 		the number of operations.
*/
void	sort_big_inputs(t_stack *stack, int pivot)
{
	int	target;

	target = stack->size - 1;
	while (target >= 0)
	{
		if (stack->head_b->index == target - 2)
		{
			push_a(stack, 1);
			rotate_a(stack, 1);
		}
		if (stack->head_b->index == target -1)
			push_a(stack, 1);
		if (stack->head_b->index == target)
			handle_target(stack, &target);
		else
		{
			if (find_target(stack, target) < pivot)
				rotate_b(stack, 1);
			else
				r_rotate_b(stack, 1);
		}
	}
}
