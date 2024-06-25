/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_environment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 19:38:19 by tdeverge          #+#    #+#             */
/*   Updated: 2023/02/13 17:36:29 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @summary:
 * 		- Fill the information about environment variable passed as parameter
 * 		('str') to a node variable and return the node.
*/
static t_variable	*set_environment_content(t_variable *var, char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	var->name = ft_substr(str, 0, i);
	if (!var->name)
		return (NULL);
	if (i == ft_strlen(str))
		var->content = NULL;
	else
	{
		var->content = ft_substr(str, i + 1, ft_strlen(str));
		if (!var->content)
			return (NULL);
	}
	return (var);
}

/*
 * @summary:
 * 		- Initialize a new node with informations passed as parameter
 * 		and add it at the end of environment linked list.
*/
static t_env	*insert_environment_node(t_env *env, char *str)
{
	t_variable	*new;
	t_variable	*tmp;

	new = malloc(sizeof(t_variable));
	if (!new)
		return (NULL);
	new = set_environment_content(new, str);
	if (!new)
		return (NULL);
	new->next = NULL;
	new->index = 0;
	if (!env->var)
		env->var = new;
	else
	{
		tmp = env->var;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (env);
}

/*
 * @summary:
 * 		- Loop through environment and add every variable to 
 * 		a linked list 'env' passed as parameter.
*/
void	get_environment(t_env *env, char **envp)
{
	int	i;

	i = 0;
	env->var = NULL;
	while (envp && envp[i])
	{
		env = insert_environment_node(env, envp[i]);
		if (!env)
		{
			free_env(env->var);
			throw_perror(1);
		}
		set_ascii_index(env);
		i++;
	}
}
