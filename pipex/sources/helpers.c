/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 23:07:02 by tdeverge          #+#    #+#             */
/*   Updated: 2023/01/22 18:14:21 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 * @summary:
 * 		- Open pipe and return array of int with both fd.
 * 		- Free paths if syscall failed and exit program.
*/
void	open_pipe(int *fd_pipe, char **paths)
{
	if (pipe(fd_pipe) == -1)
	{
		free(paths);
		throw_perror(EXIT_PIPE);
	}
}

/*
 * @summary:
 * 		- Open both infile and outfile
 * 		- Doesn't treat if open() syscall fail (later in execution)
*/
void	open_files(int	*fd_files, char *infile, char *outfile)
{
	fd_files[0] = open(infile, O_RDONLY);
	fd_files[1] = open(outfile, O_TRUNC | O_WRONLY | O_CREAT, STD_PERM);
}

/*
 * @summary:
 * 		- Use fork() syscall, save its return value and return it.
 * 		- Close pipe, free paths and exit program if the syscall fail.
*/
pid_t	start_fork(int *fd_pipe, char **paths)
{
	pid_t	pid;

	pid = 0;
	pid = fork();
	if (pid == -1)
	{
		close(fd_pipe[0]);
		close(fd_pipe[1]);
		free(paths);
		throw_perror(EXIT_FORK);
	}
	return (pid);
}

/*
 * @summary:
 * 		- Close both fds for the files and the pipe.
*/
void	close_fds(int *fd_file, int *fd_pipe)
{
	if (fd_file[0] != -1)
		close(fd_file[0]);
	if (fd_file[1] != -1)
		close(fd_file[1]);
	close(fd_pipe[0]);
	close(fd_pipe[1]);
}
