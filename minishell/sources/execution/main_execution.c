/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 01:37:30 by tdeverge          #+#    #+#             */
/*   Updated: 2023/02/15 11:21:23 by pmieuzet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @summary:
 * 		- Restore standard input and standard output to be ready to receive
 * 		new input for next prompt.
*/
static int	restore_fd(t_command *command, int fdout, int fdin)
{
	if (command->fds[0] != NO_FILE)
		close(command->fds[0]);
	if (command->fds[1] != NO_FILE)
		close(command->fds[1]);
	if (fdout > 0)
	{
		if (dup2(fdout, 1) < 0)
			return (1);
		close(fdout);
	}
	if (fdin > 0)
	{
		if (dup2(fdin, 0) < 0)
			return (1);
		close(fdin);
	}
	return (0);
}

/*
 * @summary:
 * 		- Add environment linked list to the char ** form and execute the multi
 * 		commands with pipex. Free pid and and char ** environment at the end.
*/
static int	handle_multi_command(t_list *lst, t_env *env)
{
	t_command	*command;

	command = lst->first;
	env->envp = convert_env(env);
	if (!env->envp || !initialize_pid(lst))
		return (print_perror());
	pipex(lst, env);
	free(lst->pid);
	free_matrix(env->envp);
	return (RETURN_SUCCESS);
}

/*
 * @summary:
 * 		- Save stdin and stdout and check redirections.
 * 		- Check builtins and execute the command then restore the
 * 		standard fd for the next prompt.
*/
static int	handle_single_command(t_list *lst, t_env *env)
{
	int	stdin_save;
	int	stdout_save;

	stdin_save = -1;
	stdout_save = -1;
	lst->first->fdout = 1;
	if ((!lst->first->cmd || is_builtin(lst->first)) && lst->first->redi)
	{
		stdin_save = dup(0);
		stdout_save = dup(1);
		if (!redi_manager(lst->first))
		{
			restore_fd(lst->first, stdout_save, stdin_save);
			return (RETURN_FAILURE);
		}
	}
	if (!check_builtins(lst->first, env))
		single_cmd(lst, lst->first, env);
	restore_fd(lst->first, stdout_save, stdin_save);
	return (RETURN_SUCCESS);
}

/*
 * @summary:
 * 		- Main function for execution. Handle in a different way if there
 * 		is only one command or multi-commands with pipes.
*/
int	main_execution(t_list *lst, t_env *env)
{
	modify_signals(CMD_SIGNAL);
	if (!lst || !lst->first)
		return (RETURN_FAILURE);
	else if (!lst->first->next)
	{
		if (!handle_single_command(lst, env))
			return (RETURN_FAILURE);
	}
	else
	{
		if (!handle_multi_command(lst, env))
			return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}
