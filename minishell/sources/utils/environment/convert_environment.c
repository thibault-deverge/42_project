/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_environment.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 03:22:39 by tdeverge          #+#    #+#             */
/*   Updated: 2023/02/20 09:04:51 by pmieuzet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @summary:
 * 		- Return number of variables in the environment
 * 		linked list.
*/
static int	get_nb_var(t_env *env)
{
	t_variable	*tmp;
	int			nb_var;

	nb_var = 0;
	tmp = env->var;
	while (tmp)
	{
		if (tmp->content)
			nb_var++;
		tmp = tmp->next;
	}
	return (nb_var);
}

/*
 * @summary:
 * 		- Loop throught environment linked list and convert
 * 		it to a matrix (char **).
*/
char	**convert_env(t_env	*env)
{
	char		**envp;
	t_variable	*tmp;
	int			i;

	i = 0;
	envp = malloc(sizeof(char *) * (get_nb_var(env) + 1));
	if (!envp)
		return (NULL);
	tmp = env->var;
	while (tmp)
	{
		if (tmp->content)
		{
			envp[i] = ft_sepjoin(tmp->name, tmp->content, '=');
			if (!envp[i])
			{
				free_matrix(envp);
				return (NULL);
			}
			i++;
		}
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}
