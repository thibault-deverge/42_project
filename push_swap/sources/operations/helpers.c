/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 23:57:43 by tdeverge          #+#    #+#             */
/*   Updated: 2022/12/21 01:37:54 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
 * @summary:
 * 		- Initialize the tail of a stack based on its 'stack_id' : 1 for 
 * 		stack A and 2 for stack B.
*/
void	initialize_tail(t_stack *stack, int stack_id)
{
	t_node	*temp;

	if (stack_id == 1)
	{
		temp = stack->head_a;
		while (temp->next != NULL)
			temp = temp->next;
		stack->tail_a = temp;
	}
	if (stack_id == 2)
	{
		temp = stack->head_b;
		while (temp->next != NULL)
			temp = temp->next;
		stack->tail_b = temp;
	}
}
