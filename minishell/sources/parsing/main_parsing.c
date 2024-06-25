/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:30:07 by tdeverge          #+#    #+#             */
/*   Updated: 2023/02/14 10:22:55 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*main_parsing(t_list *lst, char *cmd, t_env *env)
{
	t_parse	parse;

	parse.token = NULL;
	if (!pre_parsing(&parse, cmd, env))
	{
		free(cmd);
		free_tokens((&parse)->token);
		return (RETURN_FAILURE);
	}
	if (!parse_commands(lst, &parse))
	{
		free(cmd);
		free_commands(lst->first);
		free_tokens((&parse)->token);
		return (RETURN_FAILURE);
	}
	free_tokens((&parse)->token);
	return (lst);
}
