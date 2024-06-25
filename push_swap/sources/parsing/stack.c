/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:36:55 by tdeverge          #+#    #+#             */
/*   Updated: 2022/12/24 17:38:56 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
 * @summary:
 * 		- Initialize stack in the heap and return it.
*/
void	init_stack(t_stack *stack)
{
	stack->head_a = NULL;
	stack->tail_a = NULL;
	stack->head_b = NULL;
	stack->tail_b = NULL;
}

/*
 * @summary:
 * 		- make a node and push it to stack A. 
 * 		- If stack A is empty, the node become the top of the stack.
 * 		- add tail of stack if first push
 * 		- update min and max value
 * @params:
 * 		- *stack : pointer to the stacks.
 * 		- data : data we want push to the stack A.
 * @return:
 * 		- 0 if success.
 * 		- 1 if failure to free arg_split and stack in the calling
 * 		function.
*/
int	push_stack_parsing(t_stack *stack, int data)
{
	t_node	*temp;

	temp = make_node(data, -1);
	if (!temp)
		return (1);
	if (stack->head_a)
		temp->next = stack->head_a;
	else
		stack->tail_a = temp;
	stack->head_a = temp;
	return (0);
}
