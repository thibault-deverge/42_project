/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:51:15 by tdeverge          #+#    #+#             */
/*   Updated: 2023/01/22 18:53:35 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*
 * @summary:
 * 		- Display "err_msg" in STDERR and exit with the exit value passed
 * 		as parameter.
*/
void	throw_error(char *err_msg, size_t exit_value)
{
	ft_putstr_fd(err_msg, 2);
	exit(exit_value);
}

/*
 * @summary:
 * 		- Display error followed by the error message set via ERRNO.
 * 		- Exit with the exit value passed as parameter.
*/
void	throw_perror(size_t exit_value)
{
	perror("error");
	exit(exit_value);
}
