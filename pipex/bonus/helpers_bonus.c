/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 20:33:39 by tdeverge          #+#    #+#             */
/*   Updated: 2023/01/23 03:18:34 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*
 * @summary:
 * 		- Check if we use here_doc and open or not infile.
 * 		- Open outfile in every case.
 * 		- Does't check error (check later directly in child).
*/
static void	open_files(int	*files, int argc, char **argv)
{
	int	last;

	last = argc - 1;
	if (ft_is_heredoc(argv[1]))
	{
		files[0] = -1;
		files[1] = open(argv[last], O_WRONLY | O_APPEND | O_CREAT, STD_PERM);
	}
	else
	{
		files[0] = open(argv[1], O_RDONLY);
		files[1] = open(argv[last], O_TRUNC | O_WRONLY | O_CREAT, STD_PERM);
	}
}

/*
 * @summary:
 * 		- Open both pipes and exit the program properly if syscall
 *		failed.
*/
static void	open_pipes(int pipes[][2], int *files)
{
	if (pipe(pipes[0]) == -1 || pipe(pipes[1]) == -1)
	{
		close_files(files);
		throw_perror(EXIT_PIPE);
	}
}

/*
 * @summary:
 * 		- Open boths files and pipes.
*/
void	open_fds(t_pipex *pipex, int argc, char **argv)
{
	open_files(pipex->fd_files, argc, argv);
	open_pipes(pipex->fd_pipes, pipex->fd_files);
}

/*
 * @summary:
 * 		- Use fork() system call and return its value.
 * 		- Free dynamic memory and exit program properly if it failed. 
*/
pid_t	make_fork(t_pipex *pipex)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		free_and_exit(pipex, EXIT_FORK);
	return (pid);
}

/*
 * @summary:
 * 		- Execute dup2() system call and protect it in case it fail.
*/
void	make_dup(t_pipex *pipex, int new_fd, int old_fd)
{
	if (dup2(new_fd, old_fd) == -1)
		free_and_exit(pipex, EXIT_DUP);
}
