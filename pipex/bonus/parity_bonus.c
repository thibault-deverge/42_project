/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parity_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 23:45:02 by tdeverge          #+#    #+#             */
/*   Updated: 2023/01/23 02:34:28 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*
 * @summary:
 * 		- Dup2() first command via infile or here_doc depend the case.
 * 		- Redirect STDOUT on pipe 1.
*/
static void	make_dup_first_cmd(t_pipex *pipex, char *arg_heredoc)
{
	if (ft_is_heredoc(arg_heredoc))
		make_dup(pipex, pipex->fd_pipes[0][0], STDIN_FILENO);
	else
		make_dup(pipex, pipex->fd_files[0], STDIN_FILENO);
	make_dup(pipex, pipex->fd_pipes[1][1], STDOUT_FILENO);
}

/*
 * @summary:
 * 		- Redirect STDOUT on outfile and read on pipe 1 or 0 depend
 * 		the parity of the command.
*/
static void	make_dup_last_cmd(t_pipex *pipex, t_cmd *command)
{
	if (command->current_cmd % 2 == EVEN)
		make_dup(pipex, pipex->fd_pipes[1][0], STDIN_FILENO);
	else
		make_dup(pipex, pipex->fd_pipes[0][0], STDIN_FILENO);
	make_dup(pipex, pipex->fd_files[1], STDOUT_FILENO);
}

/*
 * @summary:
 * 		- Send to function to handle special case if command number is 1 ou last.
 * 		- Call syscall dup2() and to replace STDIN and STDOUT depend if its
 * 		a even or odd command. Protect dup2() if it fail.
*/
void	make_dup_parity(t_pipex *pipex, t_cmd *command, char *arg_heredoc)
{
	if (command->current_cmd == 1)
		make_dup_first_cmd(pipex, arg_heredoc);
	else if (command->current_cmd == command->total_cmd)
		make_dup_last_cmd(pipex, command);
	else
	{
		if (command->current_cmd % 2 == EVEN)
		{
			make_dup(pipex, pipex->fd_pipes[1][0], STDIN_FILENO);
			make_dup(pipex, pipex->fd_pipes[0][1], STDOUT_FILENO);
		}
		else
		{
			make_dup(pipex, pipex->fd_pipes[0][0], STDIN_FILENO);
			make_dup(pipex, pipex->fd_pipes[1][1], STDOUT_FILENO);
		}
	}
}

/*
 * @summary:
 * 		- Open pipe 0 if current command is even.
 * 		- Open pipe 1 if current command is odd.
 * 		- Exit program properly if pipe() syscall failed.
*/
void	open_pipe_parity(t_pipex *pipex, int current_cmd)
{
	int	return_value;

	if (current_cmd % 2 == EVEN)
		return_value = pipe(pipex->fd_pipes[0]);
	else
		return_value = pipe(pipex->fd_pipes[1]);
	if (return_value == -1)
		free_and_exit(pipex, EXIT_PIPE);
}

/*
 * @summary:
 * 		- Close pipe 1 if current command is even.
 * 		- Close pipe 0 if current command is odd.
*/
void	close_pipe_parity(int fd_pipes[][2], int current_cmd)
{
	if (current_cmd % 2 == EVEN)
	{
		close(fd_pipes[1][0]);
		close(fd_pipes[1][1]);
	}
	else
	{
		close(fd_pipes[0][0]);
		close(fd_pipes[0][1]);
	}
}
