/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   personalized_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 00:51:28 by tdeverge          #+#    #+#             */
/*   Updated: 2023/02/15 17:42:34 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @summary:
 * 		- Print a personalized error depend the source of it. Receive both
 * 		sources and messages as parameters.
 * 		- Error source will depend of the return value of the lstat syscall.
 * 		- Return global error variable.
*/
int	print_perso_error(char *err_src, char *err_msg)
{
	struct stat	buf;

	ft_putstr_fd(err_src, 2);
	ft_putstr_fd(": ", 2);
	if (!lstat(err_src, &buf)
		&& (!ft_strncmp(err_src, "./", 2) || err_src[0] == '/'))
	{
		if (S_ISDIR(buf.st_mode))
			ft_putstr_fd(ERROR_DIR, 2);
		else if (access(err_src, X_OK))
			ft_putstr_fd(ERROR_PERM, 2);
		else
			ft_putstr_fd(ERROR_OPEN_FD, 2);
		g_value = 126;
		return (g_value);
	}
	else if (ft_strncmp(err_src, "./", 2) == 0 || err_src[0] == '/')
		ft_putstr_fd(ERROR_OPEN_FD, 2);
	else
		ft_putstr_fd(err_msg, 2);
	g_value = 127;
	return (g_value);
}

/*
 * @summary:
 *		- Print a token error with the token concerned by the error
 * 		at the end.
*/
int	print_specific_error(char *err_msg, char err_arg)
{
	ft_putstr_fd(err_msg, 2);
	ft_putchar_fd('\'', 2);
	ft_putchar_fd(err_arg, 2);
	ft_putstr_fd("\'\n", 2);
	return (RETURN_FAILURE);
}

/*
 * @summary:
 * 		- Replace input with the standard one if stdin is close.
 * 		- If not, throw an error like bash would do it.
*/
int	heredoc_err(char *error, t_command *command, int stdin_dup)
{
	int	check_stdin;

	check_stdin = dup(0);
	if (check_stdin == -1)
	{
		dup2(stdin_dup, 0);
		close(stdin_dup);
		return (RETURN_FAILURE);
	}
	else
	{
		close(check_stdin);
		close(stdin_dup);
		ft_putstr_fd(ERROR_HEREDOC, 2);
		ft_putstr_fd(" (wanted \'", 2);
		ft_putstr_fd(error, 2);
		ft_putstr_fd("\')\n", 2);
	}
	if (command->fds[0] != NO_FILE)
		close(command->fds[0]);
	return (RETURN_SUCCESS);
}
