/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:49:06 by tdeverge          #+#    #+#             */
/*   Updated: 2022/12/31 00:13:23 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define  PUSH_SWAP_H

# include <stdlib.h>
# include <limits.h>
# include "./libft/includes/libft.h"

/* 
 * *******************************
 * 			STRUCTURE
 * *******************************
*/
typedef struct s_node
{
	int				data;
	int				index;
	struct s_node	*next;
}	t_node;

typedef struct s_stack
{
	t_node	*head_a;
	t_node	*tail_a;
	t_node	*head_b;
	t_node	*tail_b;
	int		size;
}	t_stack;

/* 
 * *******************************
 * 			PARSING
 * *******************************
*/
void	parsing_args(t_stack *stack, int argc, char **argv);
void	check_duplicate(t_stack *stack);
void	normalize_values(t_stack *stack);
void	init_stack(t_stack *stack);
int		push_stack_parsing(t_stack *stack, int data);
void	throw_error(void);
void	free_arg(char **arg);
void	free_stacks(t_stack *stack);
void	free_exit(t_stack *stack);
void	parsing_exit(t_stack *stack, char **arg);

/* 
 * *******************************
 * 			OPERATIONS
 * *******************************
*/
t_node	*make_node(int data, int index);
int		pop(t_stack *stack, int *index, int stack_id);
int		pop_bottom(t_stack *stack, int *index, int stack_id);
void	push(t_stack *stack, int data, int index, int stack_id);
void	push_bottom(t_stack *stack, int data, int index, int stack_id);
void	initialize_tail(t_stack *stack, int stack_id);
void	swap_a(t_stack *stack, int is_print);
void	swap_b(t_stack *stack, int is_print);
void	swap_both(t_stack *stack, int is_print);
void	push_a(t_stack *stack, int is_print);
void	push_b(t_stack *stack, int is_print);
void	rotate_a(t_stack *stack, int is_print);
void	rotate_b(t_stack *stack, int is_print);
void	rotate_both(t_stack *stack, int is_print);
void	r_rotate_a(t_stack *stack, int is_print);
void	r_rotate_b(t_stack *stack, int is_print);
void	r_rotate_both(t_stack *stack, int is_print);

/* 
 * *******************************
 * 			SORTING
 * *******************************
*/
int		sort_remaining_stack_a(t_stack *stack);
int		stack_count(t_stack *stack);
int		find_target(t_stack *stack, int target);
int		is_sorted(t_stack *stack);
int		find_pivot(t_stack *stack);
void	sort_inputs(t_stack *stack);
void	sort_small_inputs(t_stack *stack);
void	sort_big_inputs(t_stack *stack, int pivot);

#endif
