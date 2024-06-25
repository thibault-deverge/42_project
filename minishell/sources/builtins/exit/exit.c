/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 00:04:01 by tdeverge          #+#    #+#             */
/*   Updated: 2023/02/13 09:33:40 by pmieuzet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @summary:
 * 		- Print error for exit in the form bash is doing it.
*/
static int	print_error_exit(char *value, char *err_msg)
{
	g_value = 2;
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(value, 2);
	ft_putchar_fd(':', 2);
	ft_putstr_fd(err_msg, 2);
	return (0);
}

/*
 * @summary:
 * 		- Receive a string as parameter and check if every characters
 * 		is a digit.
*/
static int	is_number(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
 * @summary:
 * 		- Handle case where exit is passed with a parameter and modulo its argument
 * 		by 256 to exit with this status.
 * 		- Free and only return if there is more than two arguments.
 * 		- Free and exit with status of 2 if first argument is not a digit.
*/
static int	handle_arg(t_command *command, t_env *env, long long *status)
{
	int	limits;

	if (!is_number(command->cmd[1]))
	{
		print_error_exit(command->cmd[1], ERROR_EXIT_NUM);
		free_main_lists(command, env);
		exit(g_value);
	}
	if (command->cmd[2])
	{
		print_error_exit(command->cmd[2], ERROR_EXIT_ARG);
		g_value = 1;
		return (RETURN_FAILURE);
	}
	limits = 0;
	*status = ft_atoll(command->cmd[1], &limits);
	if (limits)
	{
		print_error_exit(command->cmd[1], ERROR_EXIT_NUM);
		free_main_lists(command, env);
		exit(g_value);
	}
	return (RETURN_SUCCESS);
}

/*
 * @summary:
 * 		- Exit with status of global variable if no arguments are passed to
 * 		the command.
 * 		- Handle in a extern function if argument(s) are passed.
*/
int	exec_exit(t_command *command, t_env *env)
{
	long long	exit_status;

	ft_putstr_fd("exit\n", 1);
	if (!command->cmd[1])
	{
		free_commands(command);
		free_env(env->var);
		exit(g_value);
	}
	else
	{
		if (!handle_arg(command, env, &exit_status))
			return (RETURN_FAILURE);
	}
	free_commands(command);
	free_env(env->var);
	g_value = exit_status % 256;
	exit(g_value);
	return (RETURN_FAILURE);
}
