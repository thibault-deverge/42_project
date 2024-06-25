/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 15:16:23 by tdeverge          #+#    #+#             */
/*   Updated: 2023/01/23 14:33:20 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 * @summary:
 * 		- Depend the command we're trying to execute, make the corresponding
 * 		dup and protect it in case the syscall dup2() fail.
*/
void	make_dup(int fd_file, t_pipex *pipex)
{
	int	first_dup;
	int	second_dup;

	if (pipex->child_index == 0)
	{
		first_dup = dup2(fd_file, 0);
		second_dup = dup2(pipex->fd_pipe[1], 1);
	}
	else
	{
		first_dup = dup2(pipex->fd_pipe[0], 0);
		second_dup = dup2(fd_file, 1);
	}
	if (first_dup == -1 || second_dup == -1)
	{
		free_matrice(pipex->paths);
		close(pipex->fd_pipe[0]);
		close(pipex->fd_pipe[1]);
		close(fd_file);
		throw_perror(EXIT_DUP);
	}
}

/*
 * @summary:
 * 		- Check if absolute path was given as argument and execute it
 * 		if it's the case.
 * 		- If only the name of the command were given, find its path in
 * 		the PATH variable and execute it.
 * 		- Free and exit properly in case the syscall execve() failed.
*/
void	exec_cmd(char **cmd_args, char **paths, char **envp)
{
	char	*cmd_path;
	int		i;

	i = 0;
	if (!access(cmd_args[0], F_OK))
		execve(cmd_args[0], cmd_args, envp);
	while (paths[i])
	{
		cmd_path = ft_joinpath(paths[i], cmd_args[0]);
		if (!access(cmd_path, F_OK))
			execve(cmd_path, cmd_args, envp);
		free(cmd_path);
		cmd_path = NULL;
		i++;
	}
	free_matrice(cmd_args);
	free_matrice(paths);
	throw_perror(EXIT_CMD);
}

/*
 * @summary:
 * 		- Print error in case file was not open properly and exit properly
 * 		the child.
 * 		- Duplicate the fds depend which child is it, find the command it need
 * 		to execute and call function to execute it.
*/
void	handle_child(t_pipex *pipex, char **argv, char **envp)
{
	char	**cmd_args;
	int		fd_file;

	fd_file = pipex->fd_file[pipex->child_index];
	if (fd_file == -1)
	{
		close_fds(pipex->fd_file, pipex->fd_pipe);
		free_matrice(pipex->paths);
		perror("error");
		exit(EXIT_PERM);
	}
	make_dup(fd_file, pipex);
	close_fds(pipex->fd_file, pipex->fd_pipe);
	cmd_args = ft_find_command(pipex->paths, argv, pipex->child_index);
	exec_cmd(cmd_args, pipex->paths, envp);
}
