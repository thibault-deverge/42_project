/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:45:32 by tdeverge          #+#    #+#             */
/*   Updated: 2023/02/12 21:45:34 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @summary:
 * 		- Copy pwd in 'pwd_buf' and print it.
*/
int	exec_pwd(t_command *command, t_env *env)
{
	char	pwd_buf[PATH_SIZE];

	(void)*command;
	(void)*env;
	if (!getcwd(pwd_buf, PATH_SIZE))
		return (print_perror());
	ft_putstr_fd(pwd_buf, 1);
	ft_putchar_fd('\n', 1);
	return (RETURN_SUCCESS);
}
