/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 01:39:33 by tdeverge          #+#    #+#             */
/*   Updated: 2022/12/21 15:15:46 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
 * @summary:
 * 		- normalise the values in a linked list to a common range to
 * 		help the efficiency of the sort algorithm.
*/
void	normalize_values(t_stack *stack)
{
	t_node	*i;
	t_node	*j;
	int		index;

	index = 0;
	i = stack->head_a;
	j = stack->head_a;
	while (i != NULL)
	{
		j = stack->head_a;
		index = 0;
		while (j)
		{
			if (i->data > j->data)
				index++;
			j = j->next;
		}
		i->index = index;
		i = i->next;
	}
}
