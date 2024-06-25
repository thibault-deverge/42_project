/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 01:44:51 by tdeverge          #+#    #+#             */
/*   Updated: 2023/02/15 11:16:26 by pmieuzet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @summary:
 * 		- Update the fd of the command depend the redirections it contains.
*/
static void	update_dup(t_command *command, int fdin, int fdout)
{
	if (fdout != NO_FILE)
		command->fds[1] = fdout;
	if (fdin != NO_FILE)
	{
		if (command->fds[0] != NO_FILE)
			close(command->fds[0]);
		command->fds[0] = fdin;
	}
	if (command->fds[1] != NO_FILE)
	{
		command->fdout = command->fds[1];
		if (dup2(command->fds[1], 1) < 0)
			return ;
		close (command->fds[1]);
	}
	if (command->fds[0] != NO_FILE)
	{
		if (dup2(command->fds[0], 0) < 0)
			return ;
		close (command->fds[0]);
	}
}

/*
 * @summary
 * 		- Open files with the valid flag depend which redirections
 * 		is passed as paramater.
 * 		- Print a special error if the syscall fail.
*/
static int	open_file(char *file, int old_fd, int status)
{
	int	new_fd;

	new_fd = -1;
	if (old_fd >= 0)
		close(old_fd);
	if (status == IN)
		new_fd = open(file, O_RDONLY);
	else if (status == OUT)
		new_fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (status == ADD_OUT)
		new_fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (new_fd < 0)
	{
		print_redi_error(file, ERROR_OPEN_FD);
		g_value = 1;
		return (-2);
	}
	return (new_fd);
}

/*
 * @summary:
 * 		- Loop through redirections and open file to the valid fd
 * 		depend which one is it.
 * 		- Update global variable and the stdin and out of the program.
*/
int	redi_manager(t_command *command)
{
	int	i;
	int	fdin;
	int	fdout;

	fdin = NO_FILE;
	fdout = NO_FILE;
	i = 0;
	while (command->redi && command->redi[i])
	{
		if (ft_strcmp(command->redi[i], "<") == 0)
			fdin = open_file(command->redi[i + 1], fdin, IN);
		else if (ft_strcmp(command->redi[i], ">") == 0)
			fdout = open_file(command->redi[i + 1], fdout, OUT);
		else if (ft_strcmp(command->redi[i], ">>") == 0)
			fdout = open_file(command->redi[i + 1], fdout, ADD_OUT);
		if (fdin == -2 || fdout == -2)
		{
			if (command->fds[0] != NO_FILE)
				close(command->fds[0]);
			return (RETURN_FAILURE);
		}
		i += 2;
	}
	update_dup(command, fdin, fdout);
	return (RETURN_SUCCESS);
}
