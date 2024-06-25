/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 21:41:07 by tdeverge          #+#    #+#             */
/*   Updated: 2023/01/23 14:31:51 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	pid_t	pid[2];

	if (argc != 5)
		throw_error(ERROR_ARGS, EXIT_ARGS);
	pipex.child_index = 0;
	pipex.paths = ft_find_path(envp);
	open_files(pipex.fd_file, argv[1], argv[4]);
	open_pipe(pipex.fd_pipe, pipex.paths);
	while (pipex.child_index < 2)
	{
		pid[pipex.child_index] = start_fork(pipex.fd_pipe, pipex.paths);
		if (pid[pipex.child_index] == 0)
			handle_child(&pipex, argv, envp);
		pipex.child_index++;
	}
	close_fds(pipex.fd_file, pipex.fd_pipe);
	free_matrice(pipex.paths);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	return (0);
}
