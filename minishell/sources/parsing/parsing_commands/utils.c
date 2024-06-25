/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:09:25 by tdeverge          #+#    #+#             */
/*   Updated: 2023/02/14 10:38:14 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @summary:
 * 		- Check if command only contains a single point and throw an error
 * 		if it's the case.
*/
int	is_single_point(t_command *command)
{
	if (!command->cmd)
		return (RETURN_SUCCESS);
	if (!ft_strcmp(command->cmd[0], ".")
		&& !command->cmd[1] && !command->redi)
	{
		print_error(ERROR_POINT);
		g_value = 2;
		return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}

/*
 * @summary:
 * 		- Check if char 'c' passed as a character is not a redirection
 * 		or a pipe (Use to check the third character of a redirection to 
 * 		check if this one is valid or not).
*/
int	is_redirection_invalid(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

/*
 * @summary:
 * 		- Check the arg passed as parameter is in a command-form.
 * 		- Use to check if command are stick to another via multiple tokens
 * 		consecutively without space between. Allow to parse them in one string.
*/
int	is_command(t_token *token)
{
	if (!token || !token->arg)
		return (0);
	if (token->arg[0] == ' ' || token->rule != COMMAND)
		return (0);
	return (1);
}

/*
 * @summary:
 * 		- Check the rule of the token to determine it can be a valid file
 * 		or not.
*/
int	is_invalid_file(int rule)
{
	if (rule == REDI || rule == SPACEBAR || rule == PIPE)
		return (1);
	return (0);
}
