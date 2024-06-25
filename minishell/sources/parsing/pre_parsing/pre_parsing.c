/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 20:16:41 by tdeverge          #+#    #+#             */
/*   Updated: 2023/02/12 20:54:15 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @summary:
 * 		- Place token receive as parameter 'new' at the end of the
 * 		linked list.
*/
static void	place_back_token(t_parse *parse, t_token *new)
{
	t_token	*tmp;
	int		index;

	index = 0;
	if (!parse->token)
		parse->token = new;
	else
	{
		tmp = parse->token;
		while (tmp->next)
		{
			tmp = tmp->next;
			index++;
		}
		tmp->next = new;
		tmp->index = index;
	}
}

/*
 * @summary:
 * 		- Add new token in the token linked list and place it at the end
 * 		of the list.
 * 		- Define the rule type
*/
t_parse	*add_new_token(char *arg, int start, int len, t_parse *parse)
{
	t_token	*new;

	if (start == len)
		return (NULL);
	new = malloc(sizeof(t_token));
	new->arg = ft_substr(arg, start, len - start);
	if (!new->arg)
		return (NULL);
	new->next = NULL;
	place_back_token(parse, new);
	if (check_argument(new->arg[0]) == -1)
		define_rule_token(parse, REDI);
	else if (new->arg[0] == '|')
		define_rule_token(parse, PIPE);
	else
		define_rule_token(parse, COMMAND);
	return (parse);
}

/*
 * @summary:
 *		- Iterate throught input and tokenize it in a linked list which contains only
 *		valid arguments to prepare second part of parsing.
*/
t_parse	*pre_parsing(t_parse *parse, char *cmd, t_env *env)
{
	int		len;
	int		start;

	start = 0;
	len = 0;
	while (cmd[len])
	{
		if (check_argument(cmd[len]) != 0)
		{
			len = manage_argument(&cmd[start], parse, len - start, env);
			if (len < 0)
				return (NULL);
			len += start;
			start = len;
		}
		else
			len++;
	}
	add_new_token(cmd, start, len, parse);
	return (parse);
}
