/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:53:53 by tdeverge          #+#    #+#             */
/*   Updated: 2023/01/23 03:25:38 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*
 * @summary:
 * 		- Add '\n' to the limiter and check if it exists.
 * 		- Read Stdin and add every entry to pipe 0 until LIMITER is found.
 * 		- Free dynamic memory and exit properly in case something failed.
*/
void	ft_parsing_heredoc(t_pipex *pipex, char **argv)
{
	char	*limiter;
	char	*str_read;

	limiter = ft_strjoin(argv[2], "\n");
	if (!limiter)
		free_and_exit(pipex, EXIT_ALLOC);
	str_read = get_next_line(0);
	while (ft_strncmp(str_read, limiter, ft_strlen(str_read)))
	{
		if (write(pipex->fd_pipes[0][1], str_read, ft_strlen(str_read)) == -1)
		{
			if (str_read)
				free(str_read);
			free(limiter);
			free_and_exit(pipex, EXIT_WRITE);
		}
		free(str_read);
		str_read = NULL;
		str_read = get_next_line(0);
	}
	free(limiter);
	free(str_read);
}

/*
 * @summary:
 * 		- Check validity of infile if current command is 1 and we're not on 
 * 		a here_doc. Exit command if it's not valid.
 * 		- Check validity of outfile if it's last command and exit command if
 * 		file is not valid.
*/
void	check_validity_file(t_pipex *pipex, t_cmd *command, char *arg_heredoc)
{
	if (command->current_cmd == 1 && !ft_is_heredoc(arg_heredoc))
	{
		if (pipex->fd_files[0] == -1)
			free_and_exit(pipex, EXIT_PERM);
	}
	else if (command->current_cmd == command->total_cmd)
	{
		if (pipex->fd_files[1] == -1)
			free_and_exit(pipex, EXIT_PERM);
	}
}

/*
 * @summary:
 * 		- Search in the 'envp' 2d array the entry for the PATH variable
 * 		and return it.
*/
char	**ft_find_paths(char **envp)
{
	char	**paths;
	int		i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH", 4))
		i++;
	paths = ft_split(envp[i], ':');
	if (!paths)
		throw_perror(EXIT_ALLOC);
	return (paths);
}

/*
 * @summary:
 * 		- Check if argument passed as parameter (argv[1]) is the string
 * 		"here_doc" and return a boolean.
*/
int	ft_is_heredoc(char *arg)
{
	if (!ft_strncmp(arg, "here_doc", ft_strlen(arg)))
		return (1);
	return (0);
}

/*
 * @summary:
 * 		- Initialize command structure and count number total of
 * 		commands we will handle depend if we use here_doc or not.
*/
void	ft_init_command(t_cmd *command, int argc, char **argv)
{
	command->current_cmd = 1;
	if (ft_is_heredoc(argv[1]))
		command->total_cmd = argc - 4;
	else
		command->total_cmd = argc - 3;
}
