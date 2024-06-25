/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:29:37 by tdeverge          #+#    #+#             */
/*   Updated: 2023/02/14 10:34:45 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @summary:
 * 		- Receive an int 'next_token' as parameter and traverse its value
 * 		throught the linked list to keep up with the parsing.
*/
static t_token	*traverse_next_token(t_token *token, int next_token)
{
	t_token	*tmp_token;
	int		i;

	i = 0;
	tmp_token = token;
	while (i < next_token)
	{
		tmp_token = tmp_token->next;
		i++;
	}
	return (tmp_token);
}

/*
 * @summary:
 * 		- Iterate through the linked list 'token' and assemble all the
 * 		consecutive commands in one string then return it.
 * 		- Use to check if multiple commands are consecutives and need to
 * 		be concatenated in one string.
*/
static int	handle_command(t_command *command, t_token *token)
{
	t_token	*token_tmp;
	char	*command_join;
	int		i;

	i = 1;
	token_tmp = token->next;
	if (token->rule == SPACEBAR || token->rule == PIPE)
		return (1);
	command_join = ft_strdup(token->arg);
	if (!command_join)
		return (print_perror());
	while (token_tmp && token_tmp->rule == COMMAND)
	{
		command_join = ft_strjoin_safe(command_join, token_tmp->arg);
		token_tmp = token_tmp->next;
		i++;
	}
	command->cmd = ft_insert_matrix(command->cmd, command_join);
	free(command_join);
	return (i);
}

/*
 * @Summary:
 * 		- Hub to manage if the matrices are commands or redirections
 * 		and send to valid function to handle it.
*/
static int	manage_commands(t_command *command, t_token *token)
{
	int	next_token;

	if (token->rule == REDI)
		next_token = handle_redirection(command, token);
	else
		next_token = handle_command(command, token);
	return (next_token);
}

/*
 * @summary:
 * 		- Check if pipe is the last token and throw a syntax error if its the
 * 		case.
 * 		- Check also if command before the pipe is empty.
*/
static int	manage_pipe(t_command *command, t_token *token)
{
	if (!is_single_point(command))
		return (RETURN_FAILURE);
	if (!token->next)
	{
		print_specific_error(ERROR_SYNTAX, '|');
		g_value = 2;
		return (RETURN_FAILURE);
	}
	if (!is_empty_command(command))
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}

/*
 * @summary:
 * 		- Iterate throught the list_tokens and populate the list_commands
 * 		with the corrects values.
 * 		- Every command will have two matrices : one with the command and its
 * 		arguments and the other with the redirections and corresponding files.
 * 		- Return 'list_commands' updated or NULL if an error occured.
*/
int	parse_commands(t_list *list_commands, t_parse *list_tokens)
{
	t_token		*token;
	t_command	*command;
	int			next_token;

	token = list_tokens->token;
	command = initialize_command();
	list_commands->first = command;
	while (token)
	{
		next_token = 1;
		if (token->rule == PIPE)
		{
			if (!manage_pipe(command, token))
				return (RETURN_FAILURE);
			command->next = initialize_command();
			command = command->next;
		}
		else
			next_token = manage_commands(command, token);
		if (!next_token)
			return (RETURN_FAILURE);
		token = traverse_next_token(token, next_token);
	}
	return (is_single_point(command));
}
