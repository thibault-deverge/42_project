/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 03:09:34 by tdeverge          #+#    #+#             */
/*   Updated: 2023/02/20 08:59:04 by pmieuzet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @summary:
 * 		- Run only when there is on one single command to handle.
*/
int	single_cmd(t_list *lst, t_command *cmd, t_env *env)
{
	char		*paths;
	pid_t		pid;
	int			status;
	int			exit_value;

	if (!lst->first->cmd)
		return (0);
	pid = fork();
	if (pid == -1)
		return (print_perror());
	if (pid == 0)
	{
		if (!redi_manager(cmd))
			return (RETURN_FAILURE);
		env->envp = convert_env(env);
		if (!env->envp)
			exit_single_child(lst, env, 1, 1);
		paths = get_environment_content(env, "PATH");
		exit_value = exec_command(cmd->cmd, paths, env->envp);
		exit_single_child(lst, env, 0, exit_value);
	}
	waitpid(pid, &status, 0);
	status_code(status);
	return (RETURN_FAILURE);
}

/*
 * @summary:
 * 		- Run only when there are multiples commands and will handle
 * 		each commands separately in a fork. 
*/
int	pipex(t_list *list_commands, t_env *env)
{
	t_command	*command;
	int			pipes[2][2];

	command = list_commands->first;
	if (pipe(pipes[0]) == -1)
		return (print_perror());
	command->fdout = pipes[0][1];
	if (!first_cmd(list_commands, pipes, env))
		return (RETURN_FAILURE);
	command = command->next;
	while (command->next)
	{
		if (pipe(pipes[1]) == -1)
			return (print_perror());
		command->fdout = pipes[1][1];
		if (!middle_cmd(list_commands, command, pipes, env))
			return (RETURN_FAILURE);
		pipes[0][0] = pipes[1][0];
		pipes[0][1] = pipes[1][1];
		command = command->next;
	}
	if (!last_cmd(list_commands, command, pipes, env))
		return (RETURN_FAILURE);
	wait_allpid(list_commands);
	return (RETURN_SUCCESS);
}
