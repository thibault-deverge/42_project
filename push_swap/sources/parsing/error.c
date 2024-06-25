/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:30:11 by tdeverge          #+#    #+#             */
/*   Updated: 2022/12/21 16:59:05 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
 * @summary :
 * 		- Print error message and exit the program.
*/
void	throw_error(void)
{
	ft_printf("Error\n");
	exit(-1);
}

/*
 * @summary:
 * 		- Free 2d array which contains every potential args when we split
 * 		the argument receive by the program.
*/
void	free_arg(char **arg)
{
	int	i;

	i = 0;
	if (!arg)
		return ;
	while (arg[i])
	{
		free(arg[i]);
		i++;
	}
	free(arg);
}

/*
 * @summary:
 * 		- Free stack A and stack B.
*/
void	free_stacks(t_stack *stack)
{
	t_node	*tmp;

	if (stack->head_a)
	{
		while (stack->head_a != NULL)
		{
			tmp = stack->head_a;
			stack->head_a = stack->head_a->next;
			free(tmp);
		}
	}
	if (stack->head_b)
	{
		while (stack->head_b != NULL)
		{
			tmp = stack->head_b;
			stack->head_b = stack->head_b->next;
			free(tmp);
		}
	}
}

/*
 * @summary:
 * 		- free the stack A
 * 		- throw an error
*/
void	free_exit(t_stack *stack)
{
	free_stacks(stack);
	throw_error();
}

/*
 * @summary:
 * 		- free the matrice which contains all the number in a arg 
 * 		- free the stack A
 * 		- throw an error
*/
void	parsing_exit(t_stack *stack, char **arg)
{
	free_arg(arg);
	free_stacks(stack);
	throw_error();
}
