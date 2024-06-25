/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:00:45 by tdeverge          #+#    #+#             */
/*   Updated: 2023/01/09 14:58:39 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
 * @summary: 
 * 		- make and initialise a node with the data passed 
 * 		as a parameter.
 * @return:
 * 		- the node created by the function.
*/
t_node	*make_node(int data, int index)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->data = data;
	if (index != -1)
		node->index = index;
	node->next = NULL;
	return (node);
}

/*
 * @summary:{
 * 		- Push a node to stack A or B depend if 1 or 2 are passed as parameters
 * 		"stack_id". It uses the data passed also as parameters.
 * @params:
 * 		- stack : structure which contains the stacks.
 * 		- data : data of the node we want to push.
 * 		- index : index of the node we are pushing.
 * 		- stack_id : 1 for stack A and 2 for stack B.
*/
void	push(t_stack *stack, int data, int index, int stack_id)
{
	t_node	*new_node;

	new_node = make_node(data, index);
	if (!new_node)
		free_exit(stack);
	if (stack_id == 1)
	{
		new_node->next = stack->head_a;
		stack->head_a = new_node;
		if (!new_node->next)
			stack->tail_a = new_node;
	}
	else if (stack_id == 2)
	{
		new_node->next = stack->head_b;
		stack->head_b = new_node;
		if (!new_node->next)
			stack->tail_b = new_node;
	}
}

/*
 * @summary:
 * 		- Push a node to a bottom a stack. It sets the tail of the stack if not set 
 * 		before and use it to push it without traversing every time the stack.
 * @params:
 * 		- stack : structure which contains the stacks.
 * 		- data : data of the node we want to push.
 * 		- index : index of the node we are pushing.
 * 		- stack_id : 1 for stack A and 2 for stack B.
*/
void	push_bottom(t_stack *stack, int data, int index, int stack_id)
{
	t_node	*new_node;

	new_node = make_node(data, index);
	if (!new_node)
		free_exit(stack);
	if (stack_id == 1)
	{
		if (!stack->tail_a)
			initialize_tail(stack, stack_id);
		stack->tail_a->next = new_node;
		stack->tail_a = new_node;
	}
	if (stack_id == 2)
	{
		if (!stack->tail_b)
			initialize_tail(stack, stack_id);
		stack->tail_b->next = new_node;
		stack->tail_b = new_node;
	}
}

/*
 * @summary:
 * 		- pop a node from stack A or B depend the value of "stack_id".
 * @params:
 * 		- stack : structure which contains the stacks.
 * 		- index : pointer to an integer which is index of the node we pop.
 * 		- stack_id : 1 for stack A and 2 for stack B.
 * @return:
 *		- the data of the node popped off the stack.
*/
int	pop(t_stack *stack, int *index, int stack_id)
{
	t_node	*temp;
	t_node	**head;
	int		data;

	if (stack_id == 1)
		head = &stack->head_a;
	else
		head = &stack->head_b;
	temp = *head;
	data = temp->data;
	*index = temp->index;
	*head = (*head)->next;
	free(temp);
	return (data);
}

/*
 * @summary:
 * 		- pop a node at the bottom of stack A or B depend 
 * 		the value of "stack_id".
 * @params:
 * 		- stack : structure which contains the stacks.
 * 		- index : pointer to an integer which is index of the node we pop.
 * 		- stack_id : 1 for stack A and 2 for stack B.
 * @return:
 *		- the data of the node popped off the stack.
*/
int	pop_bottom(t_stack *stack, int *index, int stack_id)
{
	t_node	*temp;
	int		data;

	if (stack_id == 1)
	{
		temp = stack->head_a;
		while (temp->next != stack->tail_a)
			temp = temp->next;
		*index = stack->tail_a->index;
		data = stack->tail_a->data;
		free(stack->tail_a);
		stack->tail_a = temp;
	}
	else
	{
		temp = stack->head_b;
		while (temp->next != stack->tail_b)
			temp = temp->next;
		*index = stack->tail_b->index;
		data = stack->tail_b->data;
		free(stack->tail_b);
		stack->tail_b = temp;
	}
	temp->next = NULL;
	return (data);
}
