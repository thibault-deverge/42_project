/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 17:21:19 by tdeverge          #+#    #+#             */
/*   Updated: 2023/01/23 14:03:28 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	t_cmd	command;
	pid_t	pid;

	if (argc < 5)
		throw_error(ERROR_ARGS, EXIT_ARGS);
	ft_init_command(&command, argc, argv);
	open_fds(&pipex, argc, argv);
	pipex.paths = ft_find_paths(envp);
	if (ft_is_heredoc(argv[1]))
		ft_parsing_heredoc(&pipex, argv);
	while (command.current_cmd <= command.total_cmd)
	{
		if (command.current_cmd != 1)
			open_pipe_parity(&pipex, command.current_cmd);
		pid = make_fork(&pipex);
		if (pid == 0)
			handle_child(&pipex, &command, argv, envp);
		if (command.current_cmd != command.total_cmd)
			close_pipe_parity(pipex.fd_pipes, command.current_cmd);
		command.current_cmd++;
	}
	free_all(&pipex);
	waitpid(pid, NULL, 0);
	return (0);
}
