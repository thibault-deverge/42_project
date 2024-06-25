/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 02:47:29 by tdeverge          #+#    #+#             */
/*   Updated: 2023/02/15 11:15:00 by pmieuzet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @summary:
 * 		- Initialize pid for every command before executing a multi-pipe
 * 		by looping through command linked list to know the number of command
 * 		and then initialize an array.
*/
int	initialize_pid(t_list *lst)
{
	t_command	*tmp;

	tmp = lst->first;
	lst->nb_cmd = 0;
	while (tmp)
	{
		tmp->fdout = 1;
		if (tmp->cmd)
		{
			tmp->index = lst->nb_cmd;
			lst->nb_cmd++;
		}
		else
			tmp->index = -1;
		tmp = tmp->next;
	}
	lst->pid = malloc(sizeof(int) * (lst->nb_cmd + 1));
	if (!lst->pid)
		return (print_perror());
	return (RETURN_SUCCESS);
}

/*
 * @summary:
 * 		- Loop over the pid in the structure 'command' and
 * 		wait for them to finish.
*/
void	wait_allpid(t_list *list_commands)
{
	int	i;
	int	status;

	i = 0;
	while (i < list_commands->nb_cmd)
	{
		waitpid(list_commands->pid[i], &status, 0);
		i++;
	}
	status_code(status);
}
