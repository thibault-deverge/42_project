/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:12:42 by tdeverge          #+#    #+#             */
/*   Updated: 2023/02/13 16:48:59 by pmieuzet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @summary:
 * 		- Loop throught token and join them together while file is valid.
*/
static char	*assemble_files(t_token *token, int *next_token)
{
	char	*redi_join;

	redi_join = NULL;
	while (token && !is_invalid_file(token->rule))
	{
		redi_join = ft_strjoin_safe(redi_join, token->arg);
		if (!redi_join)
		{
			print_perror();
			return (NULL);
		}
		*next_token += 1;
		token = token->next;
	}
	return (redi_join);
}

/*
 * @summary:
 * 		- Search the next file which follow the redirection found earlier
 * 		to add it to matrice 'redi' in the 't_command' structure.
 * 		- Print an error if a redirection follow another one and return (NULL)
 * 		- If valid file found, insert it to matrice and return number of token
 * 		need to be passed to continue parsing.
*/
static int	insert_file_to_redi(t_command *command, t_token *token)
{
	char	*redi_join;
	int		next_token;

	next_token = 1;
	redi_join = NULL;
	while (token)
	{
		if (token->rule == REDI || token->rule == PIPE)
			return (0);
		if (token->rule == SPACEBAR)
			next_token++;
		else
		{
			redi_join = assemble_files(token, &next_token);
			command->redi = ft_insert_matrix(command->redi, redi_join);
			free(redi_join);
			return (next_token);
		}
		token = token->next;
	}
	return (0);
}

/*
 * @summary:
 * 		- Insert redirection into matrice 'redi' in the command structure
 * 		- Check if the file associated to the redi is stick in the same token
 * 		to the redi and insert it to the matrice if it's the case.
 * 		- Return 1 if only redirection was inserted or 2 if file was stick to
 * 		redirection and de facto also inserted into the matrice.
*/
static int	insert_redirection(t_command *command, t_token *token, int redi_idx)
{
	char	*redi;

	redi = ft_substr(token->arg, 0, redi_idx);
	if (!redi)
		return (print_perror());
	command->redi = ft_insert_matrix(command->redi, redi);
	free(redi);
	redi = NULL;
	if (token->arg[redi_idx])
	{
		redi = ft_substr(token->arg, redi_idx, ft_strlen(token->arg));
		if (!redi)
			return (0);
		command->redi = ft_insert_matrix(command->redi, redi);
		free(redi);
		redi = NULL;
	}
	else
		return (1);
	return (2);
}

/*
 * @summary:
 * 		- Check if redirection is 1 or 2 character and if valid.
 * 		- Check and add word to matrice if the file follow the redirection
 * 		in the same node.
 * 		- If file targeted is not in same node, search next nodes to find it
 * 		and add it to the matrice.
 * 		- Return number of node we need to jump to continue parsing correctly.
*/
int	handle_redirection(t_command *command, t_token *token)
{
	int		nb_redi_inserted;
	int		nb_next_token;
	int		i;

	i = 1;
	if (token->arg[i] == '<' || token->arg[i] == '>')
		i++;
	if (is_redirection_invalid(token->arg[i]))
	{
		g_value = 2;
		return (print_specific_error(ERROR_SYNTAX, token->arg[i]));
	}
	nb_redi_inserted = insert_redirection(command, token, i);
	if (!nb_redi_inserted)
		return (0);
	if (nb_redi_inserted == 2)
		return (1);
	nb_next_token = insert_file_to_redi(command, token->next);
	if (!nb_next_token)
	{
		g_value = 2;
		return (print_specific_error(ERROR_SYNTAX, token->arg[i - 1]));
	}
	return (nb_next_token);
}
