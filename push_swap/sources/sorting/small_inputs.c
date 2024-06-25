/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_inputs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 22:57:32 by tdeverge          #+#    #+#             */
/*   Updated: 2022/12/30 22:35:53 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
 * @summary:
 * 		- Sort stack A when it contains only three value by enumerate all
 * 		cases.
*/
static void	sort_three_inputs(t_stack *stack)
{
	if (stack->head_a->index == 0)
	{
		if (stack->head_a->next->index == 2)
		{
			r_rotate_a(stack, 1);
			swap_a(stack, 1);
		}
	}
	else if (stack->head_a->index == 1)
	{
		if (stack->head_a->next->index == 2)
			r_rotate_a(stack, 1);
		else
			swap_a(stack, 1);
	}
	else
	{
		if (stack->head_a->next->index == 1)
		{
			swap_a(stack, 1);
			r_rotate_a(stack, 1);
		}
		else
			rotate_a(stack, 1);
	}
}

/*
 * @summary:
 * 		- 1. Find the one which is bigger between head and tail of stack A
 * 		and also check is not part of the three smaller value.
 * 		- 2. Push this bigger value to stack B or rotate stack A if both are
 * 		part of the three smaller value.
 * 		- 3. Do it until stack A only contains the three smaller value.
*/
static void	small_inputs_disassembly(t_stack *stack, int *i)
{
	while (*i > 2)
	{
		if (stack->head_a->index > stack->tail_a->index)
		{
			if (stack->head_a->index > 2)
			{
				push_b(stack, 1);
				(*i)--;
			}
			else
				rotate_a(stack, 1);
		}
		else if (stack->head_a->index < stack->tail_a->index)
		{
			if (stack->tail_a->index > 2)
			{
				r_rotate_a(stack, 1);
				push_b(stack, 1);
				(*i)--;
			}
			else
				rotate_a(stack, 1);
		}
	}
}

/*
 * @summary:
 * 		- Search for the next value on stock B, bring it to the head if its not
 * 		already the head, push it to stack A and rotate it to sort it.
*/
static void	small_inputs_reassembly(t_stack *stack, int *i)
{
	(*i)++;
	while (*i <= stack->size - 1)
	{
		if (stack->head_b->index == *i)
		{
			push_a(stack, 1);
			rotate_a(stack, 1);
			(*i)++;
		}
		else if (stack->tail_b->index == *i)
			r_rotate_b(stack, 1);
		else
		{
			if (stack->head_b->next->index == *i)
				swap_b(stack, 1);
			else
				rotate_b(stack, 1);
		}
	}
}

/*
 * @summary:
 * 		1 - Push bigger value to stack B until stack A only contains the three
 * 		smaller value. 
 * 		2 - Sort the three remaining value 
 * 		3 - Push to stack A the value in ascending order and rotate it at the end.
*/
void	sort_small_inputs(t_stack *stack)
{
	int	i;

	i = stack->size - 1;
	small_inputs_disassembly(stack, &i);
	sort_three_inputs(stack);
	small_inputs_reassembly(stack, &i);
}
