/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:52:36 by tdeverge          #+#    #+#             */
/*   Updated: 2023/02/12 21:52:37 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @summary:
 * 		- Update the ascii index of the variables in the environment after
 * 		deleting a variable.
*/
static void	update_ascii_index(int index, t_env *env)
{
	t_variable	*tmp;

	tmp = env->var;
	while (tmp)
	{
		if (tmp->index > index)
			tmp->index--;
		tmp = tmp->next;
	}
}

/*
 * @summary:
 * 		- Loop throught the environment list to the index of the variable we
 * 		need to delete, free its content and delete it. 
 * 		- Modify the link to update list.
*/
static void	delete_var(int index, t_env *env)
{
	t_variable	*tmp;
	t_variable	*tmp_del;

	tmp = env->var;
	while (tmp)
	{
		if (tmp->next->index == index)
		{
			tmp_del = tmp->next;
			tmp->next = tmp->next->next;
			free(tmp_del->name);
			free(tmp_del->content);
			free(tmp_del);
			tmp_del = NULL;
			return ;
		}
		tmp = tmp->next;
	}
}

/*
 * @summary:
 * 		- Check if argument receive is a environment variable and if its
 * 		the case, delete it. 
*/
int	exec_unset(t_command *command, t_env *env)
{
	int			i;
	int			len_cmd;
	int			index;
	t_variable	*var;

	i = 1;
	while (command->cmd[i])
	{
		len_cmd = ft_strlen(command->cmd[i]);
		if (!check_key_name(command->cmd[i], len_cmd, "unset"))
			return (RETURN_FAILURE);
		var = get_environment_node(env, command->cmd[i], len_cmd);
		if (var)
		{
			index = var->index;
			delete_var(index, env);
			update_ascii_index(index, env);
		}
		i++;
	}
	return (RETURN_SUCCESS);
}
