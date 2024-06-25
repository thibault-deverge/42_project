/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 22:41:18 by tdeverge          #+#    #+#             */
/*   Updated: 2022/12/30 22:36:22 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
 * summary:
 * 		- Counts the number of values in stack A and return it.
*/
int	stack_count(t_stack *stack)
{
	t_node	*temp;
	int		i;

	i = 0;
	temp = stack->head_a;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

/*
 * @summary:
 * 		- Search a specific value in tack B and return its distance from the
 * 		head of the stack.
*/
int	find_target(t_stack *stack, int target)
{
	t_node	*temp;
	int		i;

	temp = stack->head_b;
	i = 0;
	while (temp->index != target)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

/*
 * @summary:
 * 		- Check if stack A is sorted and return 1 if its the case or
 * 		0 otherwise.
*/
int	is_sorted(t_stack *stack)
{
	t_node	*temp;
	int		value;

	if (!stack->head_a)
		return (0);
	temp = stack->head_a->next;
	value = stack->head_a->data;
	while (temp)
	{
		if (temp->data < value)
			return (0);
		value = temp->data;
		temp = temp->next;
	}
	return (1);
}

/*
 * @summary:
 * 		- Push to stack B the remaining elements in stack A once I made chunk of 
 * 		input with the pivot.
*/
int	sort_remaining_stack_a(t_stack *stack)
{
	int	size_a;

	size_a = stack_count(stack);
	if (size_a > 1)
	{
		while (size_a > 1)
		{
			if (stack->head_a->index < stack->size - 1)
			{
				push_b(stack, 1);
				size_a--;
			}
			else
				rotate_a(stack, 1);
		}
	}
	return (size_a);
}
