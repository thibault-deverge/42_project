/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 01:44:06 by tdeverge          #+#    #+#             */
/*   Updated: 2023/02/15 17:05:10 by pmieuzet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @summary:
 * 		- Store here_doc received as one string in parameter.
*/
static int	store_str(t_command *command, char *str, int stdin_dup)
{
	if (!check_signal(stdin_dup))
		return (RETURN_FAILURE);
	if (command->fds[0] != NO_FILE)
		close(command->fds[0]);
	if (pipe(command->fds))
	{
		if (str)
			free(str);
		return (RETURN_FAILURE);
	}
	if (str && write(command->fds[1], str, ft_strlen(str)) <= 0)
	{
		free(str);
		close (command->fds[1]);
		return (RETURN_FAILURE);
	}
	close (command->fds[1]);
	command->fds[1] = NO_FILE;
	if (!command->cmd)
	{
		close(command->fds[0]);
		command->fds[0] = NO_FILE;
	}
	free(str);
	return (RETURN_SUCCESS);
}

/*
 * @summary:
 * 		- Use readline() function to read here_doc while input is 
 * 		not EOF. Join all the input together and store it as a string
 * 		in command structure.
*/
static int	set_heredoc(t_command *command, int index, int stdin_dup)
{
	char	*new_line;
	char	*content;

	content = NULL;
	new_line = readline("heredoc>");
	if (!new_line)
		return (heredoc_err(command->redi[index + 1], command, stdin_dup));
	while (ft_strcmp(new_line, command->redi[index + 1]) != 0)
	{
		content = ft_strjoin_safe(content, new_line);
		content = ft_strjoin_safe(content, "\n");
		if (!content)
			return (print_perror());
		new_line = readline("heredoc>");
		if (!new_line)
		{
			free(content);
			content = NULL;
			return (heredoc_err(command->redi[index + 1], command, stdin_dup));
		}
	}
	if (!store_str(command, content, stdin_dup))
		return (print_perror());
	return (RETURN_SUCCESS);
}

/*
 * @summary:
 * 		- Check if redirection at index is here_doc and set it if
 * 		its the case or close fd if its a file.
*/
static int	handle_heredocs(t_command *command, int *idx)
{
	int	stdin_dup;

	if (ft_strcmp(command->redi[*idx], "<<") == 0)
	{
		stdin_dup = set_signal_heredoc();
		if (!set_heredoc(command, *idx, stdin_dup))
			return (RETURN_FAILURE);
	}
	else if (ft_strcmp(command->redi[*idx], "<")
		== 0 && command->fds[0] != NO_FILE)
	{
		close(command->fds[0]);
		command->fds[0] = NO_FILE;
	}
	*idx += 2;
	return (RETURN_SUCCESS);
}

/*
 * @summary:
 * 		- Loop through the commands and handle all here_docs one by one.
*/
int	heredoc_manager(t_list *lst)
{
	t_command	*command;
	int			i;

	command = lst->first;
	while (command)
	{
		i = 0;
		command->fds[0] = NO_FILE;
		command->fds[1] = NO_FILE;
		while (command->redi && command->redi[i])
		{
			if (!handle_heredocs(command, &i))
			{
				close_all_pipes(lst, command);
				free_commands(lst->first);
				return (RETURN_FAILURE);
			}
		}
		command = command->next;
	}
	return (RETURN_SUCCESS);
}
