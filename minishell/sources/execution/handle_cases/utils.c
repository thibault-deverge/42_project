/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 01:56:16 by tdeverge          #+#    #+#             */
/*   Updated: 2023/02/15 17:42:28 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @summary:
 * 		- Dup2() the pipes to stdin and stdout depend which
 * 		command we are handling (first, middle or last).
*/
int	make_dup_cmd(int pipes[][2], int idx_cmd)
{
	if (idx_cmd == FIRST_CMD)
	{
		close(pipes[0][0]);
		if (dup2(pipes[0][1], STDOUT_FILENO) == -1)
			return (print_perror());
		close(pipes[0][1]);
	}
	else
	{
		if (dup2(pipes[0][0], STDIN_FILENO) == -1)
			return (print_perror());
		close(pipes[0][0]);
		if (idx_cmd == MIDDLE_CMD)
		{
			close(pipes[1][0]);
			if (dup2(pipes[1][1], STDOUT_FILENO) == -1)
			{
				return (print_perror());
			}
			close(pipes[1][1]);
		}
	}
	return (RETURN_SUCCESS);
}

/*
 * @summary:
 * 		- Print errno if parameter 'is_perror' is truthy.
 * 		- Free list of commands and envirornment then exit program.
*/
void	exit_child(t_list *lst, t_env *env, int is_perror, int exit_value)
{
	if (is_perror)
		print_perror();
	free_env(env->var);
	free_matrix(env->envp);
	free_commands(lst->first);
	free(lst->pid);
	if (g_value == 131)
		exit(g_value);
	exit(exit_value);
}

/*
 * @summary:
 * 		- Print errno if parameter 'is_perror' is truthy.
 * 		- Free list of commands and envirornment then exit program.
*/
void	exit_single_child(t_list *lst, t_env *env, int perror, int exit_val)
{
	if (perror)
		print_perror();
	free_env(env->var);
	free_matrix(env->envp);
	free_commands(lst->first);
	if (g_value == 131)
		exit(g_value);
	exit(exit_val);
}

/*
 * @summary:
 * 		- Print a special error to imitate bash if redirection fail.
 * 		- It uses the source of the error first then the error message.
*/
void	print_redi_error(char *err_src, char *err_msg)
{
	struct stat	buf;

	ft_putstr_fd(err_src, 2);
	ft_putstr_fd(": ", 2);
	if (!lstat(err_src, &buf))
		ft_putstr_fd(ERROR_PERM, 2);
	else
		ft_putstr_fd(err_msg, 2);
}

/*
 * @summary:
 * 		- Check at end of here_doc if SIGINT was used to terminate
 * 		the input. Restore stdin if it's the case.
*/
int	check_signal(int stdin_dup)
{
	int	check_stdin;

	check_stdin = dup(0);
	if (check_stdin == -1)
	{
		if (dup2(stdin_dup, 0))
			return (RETURN_FAILURE);
		close(stdin_dup);
	}
	else
	{
		close(check_stdin);
		close(stdin_dup);
	}
	return (RETURN_SUCCESS);
}
