/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 03:26:10 by tdeverge          #+#    #+#             */
/*   Updated: 2023/01/23 14:30:35 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*
 * @summary: 
 * 		- Join string 's1' and 's2' with the '\' between them.
 * 		- Allow to transform the name of the command to its absolute path.
*/
static char	*ft_joinpath(char const *s1, char const *s2)
{
	char			*pt_newstr;
	size_t			s1_len;
	size_t			s2_len;
	size_t			total_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	total_len = s1_len + s2_len + 1;
	pt_newstr = (char *)malloc(total_len + 1);
	if (!pt_newstr)
		return (NULL);
	ft_strlcpy(pt_newstr, s1, s1_len + 1);
	pt_newstr[s1_len] = '/';
	pt_newstr[s1_len + 1] = '\0';
	ft_strlcat(pt_newstr, s2, total_len + 1);
	return (pt_newstr);
}

/*
 * @summary:
 * 		- Split the argv corresponding to the command we want to execute.
 * 		- Return a 2d array with the command at index 0 and arguments on
 * 		the next indexes.
*/
static char	**ft_find_command(t_pipex *pipex, char **argv, int current_cmd)
{
	char	**cmd_args;

	if (ft_is_heredoc(argv[1]))
		cmd_args = ft_split(argv[current_cmd + 2], ' ');
	else
		cmd_args = ft_split(argv[current_cmd + 1], ' ');
	if (!cmd_args)
		free_and_exit(pipex, EXIT_ALLOC);
	return (cmd_args);
}

/*
 * @summary:
 * 		- Check if absolute path was given as argument and execute it
 * 		if it's the case.
 * 		- If only the name of the command were given, find its path in
 * 		the PATH variable and execute it.
 * 		- Free and exit properly in case the syscall execve() failed.
*/
static void	exec_cmd(char **cmd_args, char **paths, char **envp)
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
 * 		- Check validity of file if first or last command and exit without
 * 		doing nothing if no valid.
 * 		- Make the dup depend the position of the command.
 * 		- Close fds
 * 		- Find commands in the arguments and send it to 'exec_cmd' function
 * 		to execute it.
*/
void	handle_child(t_pipex *pipex, t_cmd *command, char **argv, char **envp)
{
	char	**cmd_args;

	check_validity_file(pipex, command, argv[1]);
	make_dup_parity(pipex, command, argv[1]);
	close_files(pipex->fd_files);
	close_pipes(pipex->fd_pipes);
	cmd_args = ft_find_command(pipex, argv, command->current_cmd);
	exec_cmd(cmd_args, pipex->paths, envp);
}
