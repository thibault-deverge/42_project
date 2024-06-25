/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_content.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:52:24 by tdeverge          #+#    #+#             */
/*   Updated: 2023/02/12 23:55:56 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @summary:
 * 		- Set content of variable empty with a value. Both variable and new value
 * 		are received as parameter.
*/
char	*set_new_content(t_variable *var, char *value)
{
	free(var->content);
	var->content = NULL;
	var->content = ft_strdup(value);
	if (!var->content)
		return (NULL);
	return (var->content);
}

/*
 * @summary:
 * 		- Add new content to a variable passed as parameter. Join with the old
 * 		value if content already exist.
*/
int	add_new_content(t_variable *var, char *value)
{
	if (!var->content)
	{
		if (!set_new_content(var, value))
			return (print_perror());
	}
	else
	{
		var->content = ft_strjoin_safe(var->content, value);
		if (!var->content)
			return (print_perror());
	}
	return (RETURN_SUCCESS);
}
