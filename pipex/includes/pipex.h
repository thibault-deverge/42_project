/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:42:24 by tdeverge          #+#    #+#             */
/*   Updated: 2023/01/23 14:31:59 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/*
 * ******************************
 * 			MACROS
 * ******************************
*/
# define ERROR_ARGS "error: number of arguments is invalid.\n"

# define EXIT_ARGS 1
# define EXIT_ALLOC 2
# define EXIT_PIPE 3
# define EXIT_FORK 4
# define EXIT_DUP 5
# define EXIT_PERM 6
# define EXIT_CMD 7

# define STD_PERM 0664
/*
 * ******************************
 * 			HEADERS
 * ******************************
*/
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include "./libft/includes/libft.h"

/*
 * ******************************
 * 			STRUCTURES
 * ******************************
*/
typedef struct s_pipex
{
	char	**paths;
	int		fd_pipe[2];
	int		fd_file[2];
	int		child_index;
}	t_pipex;

/*
 * ******************************
 * 			FUNCTIONS
 * ****************************** 
*/
/*			fork.c					*/
void	make_dup(int fd_file, t_pipex *pipex);
void	exec_cmd(char **cmd_args, char **paths, char **envp);
void	handle_child(t_pipex *pipex, char **argv, char **envp);
/*			utils.c					*/
char	**ft_find_command(char **paths, char **argv, int child_index);
char	**ft_find_path(char **envp);
char	*ft_joinpath(char const *s1, char const *s2);
/*			helpers.c				*/
void	open_files(int *fd_files, char *infile, char *outile);
void	open_pipe(int *fd_pipe, char **paths);
pid_t	start_fork(int *fd_pipe, char **paths);
void	close_fds(int *fd_file, int *fd_pipe);
/*			error.c				*/
void	free_matrice(char **matrice);
void	throw_error(char *err_mst, size_t exit_value);
void	throw_perror(size_t exit_value);

#endif
