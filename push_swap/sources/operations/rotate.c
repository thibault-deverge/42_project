/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 19:49:00 by tdeverge          #+#    #+#             */
/*   Updated: 2022/12/30 22:32:35 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
 * @function : rotate_a | rotate_b | rotate_both
 * @summary:
 * 		- Rotate the stack in a way the first element become the 
 * 		last one.
*/
void	rotate_a(t_stack *stack, int is_print)
{
	int	head_data;
	int	head_index;

	if (!stack->head_a || !stack->head_a->next)
		return ;
	head_data = pop(stack, &head_index, 1);
	push_bottom(stack, head_data, head_index, 1);
	if (is_print)
		ft_printf("ra\n");
}

void	rotate_b(t_stack *stack, int is_print)
{
	int	head_data;
	int	head_index;

	if (!stack->head_b || !stack->head_b->next)
		return ;
	head_data = pop(stack, &head_index, 2);
	push_bottom(stack, head_data, head_index, 2);
	if (is_print)
		ft_printf("rb\n");
}

void	rotate_both(t_stack *stack, int is_print)
{
	rotate_a(stack, 0);
	rotate_b(stack, 0);
	if (is_print)
		ft_printf("rr\n");
}
