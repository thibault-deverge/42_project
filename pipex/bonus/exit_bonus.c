/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 21:42:18 by tdeverge          #+#    #+#             */
/*   Updated: 2023/01/23 14:25:58 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*
 * @summary:
 * 		- Close boths files (or do nothing if doesn't exists)
*/
void	close_files(int *files)
{
	if (files[0] != -1)
		close(files[0]);
	if (files[1] != -1)
		close(files[1]);
}

/*
 * @summary:
 * 		- Close boths pipes (entry/exit).
*/
void	close_pipes(int pipes[][2])
{
	close(pipes[0][0]);
	close(pipes[0][1]);
	close(pipes[1][0]);
	close(pipes[1][1]);
}

/*
 * @summary:
 * 		- free every strings in paths variable then free the path itself.
*/
void	free_matrice(char **matrice)
{
	int	i;

	i = 0;
	while (matrice[i])
		free(matrice[i++]);
	free(matrice);
}

/*
 * @summary:
 * 		- Free dynamic memory (paths) and close both pipes and files.
*/
void	free_all(t_pipex *pipex)
{
	close_files(pipex->fd_files);
	close_pipes(pipex->fd_pipes);
	free_matrice(pipex->paths);
}

/*
 * @summary:
 * 		- Free dynamic memory used, closes the fd's opened and close
 * 		properly the program.
*/
void	free_and_exit(t_pipex *pipex, int exit_value)
{
	free_matrice(pipex->paths);
	close_files(pipex->fd_files);
	close_pipes(pipex->fd_pipes);
	throw_perror(exit_value);
}
