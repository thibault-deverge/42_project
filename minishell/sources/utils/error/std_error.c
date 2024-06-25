/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 00:53:54 by tdeverge          #+#    #+#             */
/*   Updated: 2023/02/13 00:55:39 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @summary:
 * 		- Print string passed as parameter as an error message
 * 		and return failure macro.
*/
int	print_error(char *err_msg)
{
	ft_putstr_fd(err_msg, 2);
	return (RETURN_FAILURE);
}

/*
 * @summary:
 * 		- Use perror() system call to display and error with ERRNO'
 * 		and return NULL.
*/
int	print_perror(void)
{
	perror("error");
	g_value = 1;
	return (RETURN_FAILURE);
}

/*
 * @summary:
 * 		- Display an error using perror() system call and ERRNO.
 * 		- Exit with the value passed as parameter.
*/
void	throw_perror(int exit_value)
{
	perror("error:");
	exit(exit_value);
}
