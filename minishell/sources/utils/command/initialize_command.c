/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:08:37 by tdeverge          #+#    #+#             */
/*   Updated: 2023/02/13 16:54:36 by pmieuzet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @summary:
 * 		- Check if command is empty, print error and update global
 * 		variable if its the case.
*/
int	is_empty_command(t_command *command)
{
	if (!command->cmd && !command->redi)
	{
		print_specific_error(ERROR_SYNTAX, '|');
		g_value = 2;
		return (0);
	}
	return (1);
}

/*
 * @summary:
 * 		- Initialize a structure of type 't_command', set all
 * 		its properties to NULL and return it.
*/
t_command	*initialize_command(void)
{
	t_command	*command;

	command = malloc(sizeof(t_command) * 1);
	if (!command)
	{
		perror("error");
		g_value = 1;
		return (NULL);
	}
	command->cmd = NULL;
	command->redi = NULL;
	command->next = NULL;
	return (command);
}
