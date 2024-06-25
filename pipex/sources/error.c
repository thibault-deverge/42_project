/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 22:45:55 by tdeverge          #+#    #+#             */
/*   Updated: 2023/01/23 14:45:18 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 * @summary:
 * 		- Display error message passed as parameter on STDERR
 * 		- Exit with the value define as parameter 'exit_value'
*/
void	throw_error(char *err_msg, size_t exit_value)
{
	ft_putstr_fd(err_msg, 2);
	exit(exit_value);
}

/*
 * @summary:
 * 		- Display error message using variable errno set by syscall
 * 		- Exit with the value define as parameter 'exit_value'
*/
void	throw_perror(size_t exit_value)
{
	perror("error");
	exit(exit_value);
}

/*
 * @summary:
 * 		- free every strings in paths variable then free the path itself.
*/
void	free_matrice(char **matrice)
{
	int	i;

	i = 0;
	while (matrice[i])
		free(matrice[i++]);
	free(matrice);
}
