/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 20:09:43 by tdeverge          #+#    #+#             */
/*   Updated: 2023/01/23 14:19:44 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

/*
 * ******************************
 * 			MACROS
 * ******************************
*/
# define ERROR_ARGS "error: number of arguments is invalid.\n"

# define EXIT_ARGS 1
# define EXIT_ALLOC 2
# define EXIT_PIPE 3
# define EXIT_WRITE 4
# define EXIT_FORK 5
# define EXIT_DUP 6
# define EXIT_PERM 7
# define EXIT_CMD 8

# define STD_PERM 0644

# define EVEN 0
# define ODD 1

/*
 * ******************************
 * 			HEADERS
 * ******************************
*/
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include "./libft/includes/libft.h"

/*
 * ******************************
 * 			STRUCTURES
 * ******************************
*/
typedef struct s_pipex
{
	char	**paths;
	int		fd_files[2];
	int		fd_pipes[2][2];
}	t_pipex;

typedef struct s_cmd
{
	int		current_cmd;
	int		total_cmd;
}	t_cmd;

/*
 * ******************************
 * 			FUNCTIONS
 * ****************************** 
*/
/*			fork_bonus.c		*/
void	handle_child(t_pipex *pipex, t_cmd *command, char **argv, char **envp);
/*			parity_bonus.c		*/
void	make_dup_parity(t_pipex *pipex, t_cmd *command, char *arg_heredoc);
void	open_pipe_parity(t_pipex *pipex, int current_cmd);
void	close_pipe_parity(int fd_pipes[][2], int current_cmd);
/*			utils_bonus.c		*/
void	check_validity_file(t_pipex *pipex, t_cmd *command, char *arg_heredoc);
void	ft_init_command(t_cmd *command, int argc, char **argv);
void	ft_parsing_heredoc(t_pipex *pipex, char **argc);
char	**ft_find_paths(char **envp);
int		ft_is_heredoc(char *arg);
/*			helpers_bonus.c		*/
void	open_fds(t_pipex *pipex, int argc, char **argv);
pid_t	make_fork(t_pipex *pipex);
void	make_dup(t_pipex *pipex, int new_fd, int old_fd);
/*			exit_bonus.c		*/
void	free_and_exit(t_pipex *pipex, int exit_value);
void	free_all(t_pipex *pipex);
void	close_files(int *files);
void	close_pipes(int pipes[][2]);
void	free_matrice(char **matrice);
/*			errors_bonus.c		*/
void	throw_error(char *err_msg, size_t exit_value);
void	throw_perror(size_t exit_value);

#endif
