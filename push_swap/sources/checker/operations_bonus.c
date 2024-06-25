/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 23:26:31 by tdeverge          #+#    #+#             */
/*   Updated: 2023/01/09 14:19:40 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

/*
 *@summary:
 *		- Free stacks, the operation, throw an error message and exit the
 *		program properly.
*/
void	exit_checker(t_stack *stack, char *op)
{
	free_stacks(stack);
	free(op);
	throw_error();
}

/*
 * @summary:
 * 		- check if stack A is sorted and stack B is empty. print 'OK' if its
 * 		the case or 'KO' otherwise.
*/
void	checker_is_sorted(t_stack *stack)
{
	if (!is_sorted(stack) || stack->head_b)
		ft_printf("KO\n");
	else
		ft_printf("OK\n");
}

/*
 * @summary:
 * 		- Read operations on the standard input and execute it.
*/
void	read_operations(t_stack *stack)
{
	char	*operation;

	operation = get_next_line(0);
	while (operation && operation[0] != '\n')
	{
		do_operation(stack, operation);
		free(operation);
		operation = get_next_line(0);
	}
	free(operation);
}

/*
 * @summary:
 * 		- Check for each node which operation is it and do it without
 * 		printing it.
*/
void	do_operation(t_stack *stack, char *op)
{
	if (!ft_strncmp(op, "pa\n", ft_strlen(op)))
		push_a(stack, 0);
	else if (!ft_strncmp(op, "pb\n", ft_strlen(op)))
		push_b(stack, 0);
	else if (!ft_strncmp(op, "sa\n", ft_strlen(op)))
		swap_a(stack, 0);
	else if (!ft_strncmp(op, "sb\n", ft_strlen(op)))
		swap_b(stack, 0);
	else if (!ft_strncmp(op, "ss\n", ft_strlen(op)))
		swap_both(stack, 0);
	else if (!ft_strncmp(op, "ra\n", ft_strlen(op)))
		rotate_a(stack, 0);
	else if (!ft_strncmp(op, "rb\n", ft_strlen(op)))
		rotate_b(stack, 0);
	else if (!ft_strncmp(op, "rr\n", ft_strlen(op)))
		rotate_both(stack, 0);
	else if (!ft_strncmp(op, "rra\n", ft_strlen(op)))
		r_rotate_a(stack, 0);
	else if (!ft_strncmp(op, "rrb\n", ft_strlen(op)))
		r_rotate_b(stack, 0);
	else if (!ft_strncmp(op, "rrr\n", ft_strlen(op)))
		r_rotate_both(stack, 0);
	else
		exit_checker(stack, op);
}
