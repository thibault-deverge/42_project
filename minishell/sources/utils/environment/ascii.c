/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ascii.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 19:19:57 by tdeverge          #+#    #+#             */
/*   Updated: 2023/02/12 19:21:11 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @summary:
 * 		- Compare last element added with every other element and update 
 * 		its index everytime the last element is bigger than another one
 * 		in ASCII.
*/
void	set_ascii_index(t_env *env)
{
	t_variable	*tmp_env;
	t_variable	*tmp_var;

	tmp_var = env->var;
	tmp_env = env->var;
	while (tmp_var->next)
		tmp_var = tmp_var->next;
	while (tmp_env != tmp_var)
	{
		if (strcmp(tmp_var->name, tmp_env->name) > 0)
			tmp_var->index++;
		else
			tmp_env->index++;
		tmp_env = tmp_env->next;
	}
}
