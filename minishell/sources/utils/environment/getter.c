/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 19:38:47 by tdeverge          #+#    #+#             */
/*   Updated: 2023/02/12 23:35:32 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @summary:
 * 		- Search in environment via name of the variable passed as parameter
 * 		and return its content.
*/
char	*get_environment_content(t_env *env, char *var_name)
{
	t_variable	*tmp;

	tmp = env->var;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, var_name))
			return (tmp->content);
		tmp = tmp->next;
	}
	return (0);
}

/*
 * @summary:
 * 		- Search in environment via name of the variable passed as parameter
 * 		and return its pointer.
*/
t_variable	*get_environment_node(t_env *env, char *var_name, int len)
{
	t_variable	*tmp;

	tmp = env->var;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, var_name, ft_strlen(tmp->name)) == 0
			&& ft_strncmp(tmp->name, var_name, len) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

/*
 * @summary:
 * 		- Loop throught environment linked list and return the last node.
*/
t_variable	*get_last_var(t_env *env)
{
	t_variable	*tmp;

	if (!env->var)
		return (NULL);
	tmp = env->var;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}
