/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 14:03:10 by tdeverge          #+#    #+#             */
/*   Updated: 2022/12/21 14:36:48 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
 * @summary:
 * 		- Check if some arguments are duplicate and exit the program with
 * 		an error if yes.
*/
void	check_duplicate(t_stack *stack)
{
	t_node	*i;
	t_node	*j;

	i = stack->head_a;
	while (i != NULL)
	{
		j = i->next;
		while (j != NULL)
		{
			if (i->data == j->data)
				free_exit(stack);
			j = j->next;
		}
		i = i->next;
	}
}
