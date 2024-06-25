/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 01:16:33 by tdeverge          #+#    #+#             */
/*   Updated: 2022/12/30 22:33:04 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
 * @function:
 * 		- swap_a & swap_b 
 * @summary:
 * 		- Swap the top two elements on a stack.
 * 		- 1. pop head and second element of the stack.
 * 		- 2. push head element first then second on the stack.
 * @params:
 * 		- stack : structure which contains both stacks.
 * 		- is_print : boolean to print (1) or not (0) the operation.
*/
void	swap_a(t_stack *stack, int is_print)
{
	int	head_data;
	int	head_index;
	int	second_data;
	int	second_index;

	if (!stack->head_a || !stack->head_a->next)
		return ;
	head_data = pop(stack, &head_index, 1);
	second_data = pop(stack, &second_index, 1);
	push(stack, head_data, head_index, 1);
	push(stack, second_data, second_index, 1);
	if (is_print)
		ft_printf("sa\n");
}

void	swap_b(t_stack *stack, int is_print)
{
	int	head_data;
	int	head_index;
	int	second_data;
	int	second_index;

	if (!stack->head_b || !stack->head_b->next)
		return ;
	head_data = pop(stack, &head_index, 2);
	second_data = pop(stack, &second_index, 2);
	push(stack, head_data, head_index, 2);
	push(stack, second_data, second_index, 2);
	if (is_print)
		ft_printf("sb\n");
}

void	swap_both(t_stack *stack, int is_print)
{
	swap_a(stack, 0);
	swap_b(stack, 0);
	if (is_print)
		ft_printf("ss\n");
}
