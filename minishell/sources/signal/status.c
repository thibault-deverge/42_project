/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 03:18:07 by tdeverge          #+#    #+#             */
/*   Updated: 2023/02/13 16:18:50 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @summary:
 * 		- Update global error variable depend the result of function
 * 		WIFEXITED and WIFSIGNALED.
*/
void	status_code(int status)
{
	int	num_signal;

	if (WIFEXITED(status))
		g_value = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		num_signal = WTERMSIG(status);
		if (num_signal == 2)
			g_value = 130;
		else if (num_signal == 3)
			g_value = 131;
	}
}
