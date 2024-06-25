/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:50:28 by tdeverge          #+#    #+#             */
/*   Updated: 2023/02/13 19:10:53 by pmieuzet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @summary:
 * 		- Get length of the key of the environment variable and return it.
*/
static int	get_key_len(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	if (!var[i])
		return (RETURN_FAILURE);
	return (i);
}

/*
 * @summary:
 * 		- Manage key of environment variable and add new_variable if it's
 * 		valid. Return the variable at the end of function.
*/
static t_variable	*manage_key(char *new_var, int key_len, t_env *env)
{
	t_variable	*var_env;

	var_env = get_environment_node(env, new_var, key_len);
	if (var_env && ft_strcmp(var_env->name, "_") == 0)
	{
		g_value = 0;
		return (NULL);
	}
	if (var_env)
		return (var_env);
	else if (check_key_name(new_var, key_len, "export"))
	{
		if (!add_new_variable(new_var, key_len, env))
		{
			print_perror();
			return (RETURN_FAILURE);
		}
		return (get_last_var(env));
	}
	else
		return (NULL);
}

/*
 * @summary:
 * 		- Check validity of key receive as parameter as name of
 * 		environment variable.
*/
int	check_key_name(char *key, int len, char *built)
{
	int	i;

	i = 0;
	if (!ft_isalpha(key[0]) && key[0] != '_')
	{
		g_value = 1;
		return (export_error(built, key, INVALID_KEY));
	}
	while (i < len)
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
		{
			g_value = 1;
			return (export_error(built, key, INVALID_KEY));
		}
		i++;
	}
	if (ft_strncmp(key, "_", len) == 0)
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}

/*
 * @summary:
 * 		- Handle the case where export is passed with an argument and create
 * 		a variable with it if the argument is valid.
*/
int	manage_variable(char *new_var, t_env *env)
{
	int			key_len;
	t_variable	*var_env;

	key_len = get_key_len(new_var);
	if (!key_len)
	{
		if (!manage_key(new_var, ft_strlen(new_var), env))
			return (RETURN_FAILURE);
	}
	else if (new_var[key_len - 1] == '+')
	{
		var_env = manage_key(new_var, key_len - 1, env);
		if (!var_env || !add_new_content(var_env, &new_var[key_len + 1]))
			return (RETURN_FAILURE);
	}
	else
	{
		var_env = manage_key(new_var, key_len, env);
		if (!var_env)
			return (RETURN_FAILURE);
		else if (!set_new_content(var_env, &new_var[key_len + 1]))
			return (print_perror());
	}
	return (RETURN_SUCCESS);
}
