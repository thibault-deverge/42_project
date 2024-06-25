/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 02:37:31 by tdeverge          #+#    #+#             */
/*   Updated: 2023/02/15 11:27:56 by pmieuzet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @summary:
 * 		- Check if files are open and close them if they are.
*/
void	close_files(t_command *command)
{
	if (command->fds[0] != -1)
		close(command->fds[0]);
	if (command->fds[1] != -1)
		close(command->fds[1]);
	command->fds[0] = NO_FILE;
	command->fds[1] = NO_FILE;
}

/*
 * @summary:
 * 		- Iterate through the linked list 'list_commands' and check in each
 *		command if pipes of here_doc are open and close them if they are.
*/
void	close_heredoc(t_list *list_commands)
{
	t_command	*command;

	command = list_commands->first;
	while (command)
	{
		if (command->fds[0] != NO_FILE)
			close(command->fds[0]);
		command = command->next;
	}
}

/*
 * @summary:
 * 		- Close pipe passed as parameter.
*/
void	close_pipe(int *pipe)
{
	close(pipe[0]);
	close(pipe[1]);
}

/*
 * @summary:
 * 		- Close all pipes opened for the heredocs.
*/
void	close_all_pipes(t_list *lst, t_command *command)
{
	t_command	*tmp;

	tmp = lst->first;
	while (tmp && tmp != command)
	{
		if (tmp->fds[0] != NO_FILE)
			close(tmp->fds[0]);
		if (tmp->fds[1] != NO_FILE)
			close(tmp->fds[1]);
		tmp = tmp->next;
	}
	if (tmp->fds[0] != NO_FILE)
		close(tmp->fds[0]);
	if (tmp->fds[1] != NO_FILE)
		close(tmp->fds[1]);
}

/*
 * @summary:
 * 		- Call close_files function.
 *		- Close fdin and fdout of pipe if they are opened.
*/
int	close_all(t_command *command, int fdin, int fdout)
{
	close_files(command);
	close(fdin);
	if (fdout != NO_FILE)
		close(fdout);
	return (RETURN_SUCCESS);
}
