/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 00:17:57 by tdeverge          #+#    #+#             */
/*   Updated: 2022/12/29 00:19:30 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
 * @summary
 * 		- Check if stack A is already sorted and sort it if not. The method
 * 		used will depend the number of element stack A contains.
*/
void	sort_inputs(t_stack *stack)
{
	int	pivot;

	stack->size = stack_count(stack);
	if (is_sorted(stack))
		return ;
	if (stack->size < 10)
		sort_small_inputs(stack);
	else
	{
		pivot = find_pivot(stack);
		sort_big_inputs(stack, pivot);
	}
}
