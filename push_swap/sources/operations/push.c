/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 21:33:37 by tdeverge          #+#    #+#             */
/*   Updated: 2022/12/30 22:30:16 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
 * @summary:
 * 		- Moves top element from stack B to stack A. First pop stack B then
 * 		push value to stack A.
*/
void	push_a(t_stack *stack, int is_print)
{
	int	data;
	int	index;

	index = -1;
	if (!stack->head_b)
		return ;
	data = pop(stack, &index, 2);
	push(stack, data, index, 1);
	if (is_print)
		ft_printf("pa\n");
}

/*
 * @summary:
 * 		- Moves top element from stack A to stack B. First pop stack A then
 * 		push value to stack B.
*/
void	push_b(t_stack *stack, int is_print)
{
	int	data;
	int	index;

	index = -1;
	if (!stack->head_a)
		return ;
	data = pop(stack, &index, 1);
	push(stack, data, index, 2);
	if (is_print)
		ft_printf("pb\n");
}
