/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:53:56 by tdeverge          #+#    #+#             */
/*   Updated: 2023/01/09 18:21:03 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
 * @summary: 
 * 		- Count number of potential num contains the string passed as
 * 		an argument
 * @params:
 * 		- args_split : array of the potentials arguments in the string
 * 		passed as argument of the program.
*/
static int	count_args(char **args_split)
{
	int	i;

	i = 0;
	while (args_split[i])
		i++;
	return (i);
}

/*
 * @summary:
 * 		- helper function to check number of arguments and exit the program
 * 		if no arguments are passed to it.
*/
static void	check_arg_nb(int argc)
{
	if (argc < 2)
		exit(EXIT_FAILURE);
}

/*
 * @summary:
 * 		- Check for the 'arg' if its a valid integer to parse into
 * 		the stack and convert it to an integer if its the case.
 * @params:
 * 		- stack : structure which contains the stacks.
 * 		- args_split : array of the potentials arguments int the string
 * 		passed as argument of the program.
 * 		- arg: potential argument checked for its validity.
 * @return:
 * 		- int : the valid argument convert to an int.
*/
static int	check_arg(t_stack *stack, char **args_split, char *arg)
{
	long	arg_value;
	int		i;

	i = 1;
	if (!ft_isdigit(arg[0]) && arg[0] != '+' && arg[0] != '-')
		parsing_exit(stack, args_split);
	if ((arg[0] == '+' || arg[0] == '-') && !arg[1])
		parsing_exit(stack, args_split);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			parsing_exit(stack, args_split);
		i++;
	}
	arg_value = ft_latoi(arg);
	if (arg_value < INT_MIN || arg_value > INT_MAX)
		parsing_exit(stack, args_split);
	return (arg_value);
}

/*
 * @summary:
 * 		- Check if at least one arguments is passed to program
 * 		- Split every strings passed as an arguments to parse every number
 * 		individually and push them to the stack A if valid.
*/
void	parsing_args(t_stack *stack, int argc, char **argv)
{
	char	**arg_split;
	int		arg_value;
	int		i;

	check_arg_nb(argc);
	while (argc > 1)
	{
		arg_split = ft_split(argv[argc - 1], ' ');
		if (!arg_split || !arg_split[0])
			parsing_exit(stack, arg_split);
		i = count_args(arg_split) - 1;
		while (i >= 0)
		{
			arg_value = check_arg(stack, arg_split, arg_split[i]);
			if (push_stack_parsing(stack, arg_value))
				parsing_exit(stack, arg_split);
			i--;
		}
		free_arg(arg_split);
		arg_split = NULL;
		argc--;
	}
}
