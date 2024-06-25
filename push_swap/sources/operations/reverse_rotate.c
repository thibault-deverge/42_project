/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 21:47:35 by tdeverge          #+#    #+#             */
/*   Updated: 2022/12/30 22:31:37 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
 * @function : r_rotate_a | r_rotate_b | r_rotate_both
 * @summary:
 * 		- Inverse rotation of the stack in a way the last element become
 * 		the first one.
*/
void	r_rotate_a(t_stack *stack, int is_print)
{
	int	data;
	int	index;

	if (!stack->tail_a || stack->head_a == stack->tail_a)
		return ;
	data = pop_bottom(stack, &index, 1);
	push(stack, data, index, 1);
	if (is_print)
		ft_printf("rra\n");
}

void	r_rotate_b(t_stack *stack, int is_print)
{
	int	data;
	int	index;

	if (!stack->tail_b || stack->head_b == stack->tail_b)
		return ;
	data = pop_bottom(stack, &index, 2);
	push(stack, data, index, 2);
	if (is_print)
		ft_printf("rrb\n");
}

void	r_rotate_both(t_stack *stack, int is_print)
{
	r_rotate_a(stack, 0);
	r_rotate_b(stack, 0);
	if (is_print)
		ft_printf("rrr\n");
}
