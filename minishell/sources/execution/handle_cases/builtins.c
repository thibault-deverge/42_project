/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 01:50:24 by tdeverge          #+#    #+#             */
/*   Updated: 2023/02/15 17:23:10 by pmieuzet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @summary:
 * 		- Initialize the singleton for the built-in.
*/
static const t_builtins	*get_builtins(void)
{
	static const t_builtins	builtins[7] = {{"export", exec_export}, \
										{"env", exec_env}, \
										{"echo", exec_echo}, \
										{"unset", exec_unset}, \
										{"pwd", exec_pwd}, \
										{"cd", exec_cd}, \
										{"exit", exec_exit}};

	return (builtins);
}

/*
 * @summary:
 * 		- Call singleton structure and check which builtin we need to
 * 		execute as a command.
*/
int	is_builtin(t_command *command)
{
	const t_builtins	*builtins;
	int					i;

	builtins = get_builtins();
	i = 0;
	while (i < 7)
	{
		if (command->cmd && ft_strcmp(command->cmd[0], builtins[i].name) == 0)
			return (1);
		i++;
	}
	return (0);
}

/*
 * @summary:
 * 		- Check which builtin we need to execute and execute it.
 * 		- Update the global error variable depend the result of the built-in.
*/
int	check_builtins(t_command *command, t_env *env)
{
	const t_builtins	*builtins;
	int					i;

	builtins = get_builtins();
	i = 0;
	if (command->next && !command->next->cmd)
		return (1);
	while (i < 7)
	{
		if (command->cmd && ft_strcmp(command->cmd[0], builtins[i].name) == 0)
		{
			if (!builtins[i].f(command, env))
			{
				g_value = 1;
				return (-1);
			}
			g_value = 0;
			return (1);
		}
		i++;
	}
	return (0);
}
