/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:36:23 by tdeverge          #+#    #+#             */
/*   Updated: 2023/02/12 23:40:35 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @summary:
 * 		- Add a new variable in the environment with name passed as parameter.
*/
t_variable	*add_new_variable(char *name, int len, t_env *env)
{
	t_variable	*new;
	t_variable	*tmp;

	new = malloc(sizeof(t_variable));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->index = 0;
	if (!env->var)
		env->var = new;
	else
	{
		tmp = get_last_var(env);
		tmp->next = new;
	}
	new->name = ft_substr(name, 0, len);
	if (!new->name)
		return (NULL);
	new->content = NULL;
	set_ascii_index(env);
	return (new);
}
