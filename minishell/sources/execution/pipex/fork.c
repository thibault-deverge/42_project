/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 02:52:16 by tdeverge          #+#    #+#             */
/*   Updated: 2023/02/15 17:21:19 by pmieuzet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @summary:
 * 		- Check if it's an absolute path or not. Send in execve() syscall
 * 		if it is.
*/
static int	is_absolute_path(char **command, char **env, char **paths_split)
{
	if (!access(command[0], F_OK | X_OK))
	{
		if (execve(command[0], command, env))
		{
			free_matrix(paths_split);
			return (RETURN_FAILURE);
		}
		return (RETURN_SUCCESS);
	}
	return (RETURN_SUCCESS);
}

/*
 * @summary:
 * 		- Split the paths as parameter to have a matrix of paths.
 * 		- Check if command typed by the user is full path and 
 * 		execute it if its the case.
 * 		- Try name of the command with every path given and execute 
 * 		once the valid path was found.
*/
int	exec_command(char **command, char *paths, char **env)
{
	char	**paths_split;
	char	*command_path;
	int		i;

	i = 0;
	paths_split = NULL;
	if (paths)
	{
		paths_split = ft_split(paths, ':');
		if (!paths_split)
			return (print_perror());
	}
	if (!is_absolute_path(command, env, paths_split))
		return (print_perso_error(command[0], ERROR_TEST));
	while (paths_split && paths_split[i])
	{
		command_path = ft_joinpath(paths_split[i], command[0]);
		if (!access(command_path, F_OK | X_OK))
			execve(command_path, command, env);
		free(command_path);
		i++;
	}
	free_matrix(paths_split);
	return (print_perso_error(command[0], ERROR_TEST));
}

/*
 * @summary:
 * 		- Make a fork and get path in the environment.
 * 		- Dup fds of pipe passed as parameter for stdout and close
 * 		them all unless the standards ones.
 * 		- Check if it's necessary to redirect into files and close
 * 		the one used.
 * 		- Execute the command and exit the fork.
*/
int	first_cmd(t_list *list_cmd, int pipes[][2], t_env *env)
{
	char	*paths;
	int		exit_value;

	exit_value = 0;
	if (!list_cmd->first->cmd)
		return (close_all(list_cmd->first, pipes[0][1], NO_FILE));
	list_cmd->pid[0] = fork();
	if (list_cmd->pid[0] == 0)
	{
		modify_signals(FORK_SIGNAL);
		paths = get_environment_content(env, "PATH");
		if (!make_dup_cmd(pipes, FIRST_CMD))
			exit_child(list_cmd, env, 1, 1);
		if (!redi_manager(list_cmd->first))
			exit_child(list_cmd, env, 0, 1);
		close_heredoc(list_cmd);
		if (check_builtins(list_cmd->first, env) == 0)
			exit_value = exec_command(list_cmd->first->cmd, paths, env->envp);
		exit_child(list_cmd, env, 0, exit_value);
	}
	return (close_all(list_cmd->first, pipes[0][1], NO_FILE));
}

int	last_cmd(t_list *lst, t_command *cmd, int pipes[][2], t_env *env)
{
	char	*paths;
	int		exit_value;

	exit_value = 0;
	if (!cmd->cmd)
		return (close_all(cmd, pipes[0][0], NO_FILE));
	lst->pid[cmd->index] = fork();
	if (lst->pid[cmd->index] == -1)
		return (print_perror());
	if (lst->pid[cmd->index] == 0)
	{
		modify_signals(FORK_SIGNAL);
		paths = get_environment_content(env, "PATH");
		if (!make_dup_cmd(pipes, LAST_CMD))
			exit_child(lst, env, 1, 1);
		if (!redi_manager(cmd))
			exit_child(lst, env, 0, 1);
		close_heredoc(lst);
		if (check_builtins(cmd, env) == 0)
			exit_value = exec_command(cmd->cmd, paths, env->envp);
		exit_child(lst, env, 0, exit_value);
	}
	return (close_all(cmd, pipes[0][0], NO_FILE));
}

int	middle_cmd(t_list *lst, t_command *cmd, int pipes[][2], t_env *env)
{
	char	*paths;
	int		exit_value;

	exit_value = 0;
	if (!cmd->cmd)
		return (close_all(cmd, pipes[0][0], pipes[1][1]));
	lst->pid[cmd->index] = fork();
	if (lst->pid[cmd->index] == -1)
		return (print_perror());
	if (lst->pid[cmd->index] == 0)
	{
		modify_signals(FORK_SIGNAL);
		paths = get_environment_content(env, "PATH");
		if (!make_dup_cmd(pipes, MIDDLE_CMD))
			exit_child(lst, env, 1, 1);
		if (!redi_manager(cmd))
			exit_child(lst, env, 0, 1);
		close_heredoc(lst);
		if (check_builtins(cmd, env) == 0)
			exit_value = exec_command(cmd->cmd, paths, env->envp);
		exit_child(lst, env, 0, exit_value);
	}
	return (close_all(cmd, pipes[0][0], pipes[1][1]));
}
