/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 22:56:46 by tdeverge          #+#    #+#             */
/*   Updated: 2023/01/09 14:09:31 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include <stdlib.h>
# include "./libft/includes/libft.h"

/* 
 * *******************************
 * 			STRUCTURE
 * *******************************
*/
/*			stack				*/
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
 * *****************************
 * 			CHECKER
 * *****************************
*/
void		exit_checker(t_stack *stack, char *op);
void		checker_is_sorted(t_stack *stack);
void		read_operations(t_stack *stack);
void		do_operation(t_stack *stack, char *op);

/* 
 * *****************************
 * 			COMMON
 * *****************************
*/
/*			parsing			  */
void		parsing_args(t_stack *stack, int argc, char **argv);
void		check_duplicate(t_stack *stack);
void		init_stack(t_stack *stack);
void		throw_error(void);
void		free_stacks(t_stack *stack);
/*			operations	 	  */
t_node		*make_node(int data, int index);
void		push(t_stack *stack, int data, int index, int stack_id);
void		push_bottom(t_stack *stack, int data, int index, int stack_id);
int			pop(t_stack *stack, int *index, int stack_id);
int			pop_bottom(t_stack *stack, int *index, int stack_id);
int			is_sorted(t_stack *stack);
void		initialize_tail(t_stack *stack, int stack_id);
void		swap_a(t_stack *stack, int is_print);
void		swap_b(t_stack *stack, int is_print);
void		swap_both(t_stack *stack, int is_print);
void		push_a(t_stack *stack, int is_print);
void		push_b(t_stack *stack, int is_print);
void		rotate_a(t_stack *stack, int is_print);
void		rotate_b(t_stack *stack, int is_print);
void		rotate_both(t_stack *stack, int is_print);
void		r_rotate_a(t_stack *stack, int is_print);
void		r_rotate_b(t_stack *stack, int is_print);
void		r_rotate_both(t_stack *stack, int is_print);

#endif
