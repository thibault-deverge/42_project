/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pivot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 23:57:39 by tdeverge          #+#    #+#             */
/*   Updated: 2022/12/31 00:30:15 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
 * @summary:
 * 		- Push element to stack B if inferior to pivot and rotate it if
 * 		inferior to half-size of chunk checked to follow butterfly algorithm.
 * 		This make the element faster to retrieve in the reassembling phase.
*/
static void	sort_pivot_inferior(t_stack *stack, int p, int chunk, int *is_rrr)
{
	if (*is_rrr)
	{
		rotate_b(stack, 1);
		*is_rrr = 0;
	}
	push_b(stack, 1);
	if (stack->head_b->index < (p - chunk))
		*is_rrr = 1;
}

/*
 * @summary:
 * 		- Rotate stack A if element is superior to pivot or rotate both if
 * 		the last action saved was to rotate stack B.
*/
static void	sort_pivot_superior(t_stack *stack, int *is_rrr)
{
	if (*is_rrr)
	{
		rotate_both(stack, 1);
		*is_rrr = 0;
	}
	else
		rotate_a(stack, 1);
}

/*
 * @summary:
 * 		- Sort the elements by pushing the ones inferior to the pivot to
 * 		stack B following a variant of butterfly algorithm.
*/
static void	sort_pivot(t_stack *stack, int pivot, int n)
{
	int	chunk_size;
	int	is_rrr;

	is_rrr = 0;
	chunk_size = n / 2;
	while (n > 0)
	{
		if (stack->head_a->index < pivot)
		{
			sort_pivot_inferior(stack, pivot, chunk_size, &is_rrr);
			n--;
		}
		else
			sort_pivot_superior(stack, &is_rrr);
	}
	if (is_rrr)
		rotate_b(stack, 1);
}

/*
 * @summary:
 * 		- Find pivot which is the size of every chunk we will use to implement
 * 		a variant of a butterfly algorithm.
*/
static int	divide_stack(t_stack *stack, int n)
{
	int	pivot;
	int	i;

	i = 1;
	pivot = stack->size / n;
	while (i < n)
	{
		sort_pivot(stack, pivot * i, pivot);
		i++;
	}
	stack->size -= sort_remaining_stack_a(stack);
	return (pivot);
}

/*
 * @summary:
 * 		- Divide the elements in Stack A in few chunk depend the number
 * 		of inputs. Return the pivot which is the size of the chunks.
*/
int	find_pivot(t_stack *stack)
{
	int	pivot;

	if (stack->size > 200)
		pivot = divide_stack(stack, 10);
	else if (stack->size > 50)
		pivot = divide_stack(stack, 4);
	else
		pivot = divide_stack(stack, 2);
	return (pivot);
}
