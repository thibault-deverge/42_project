/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_minishell.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:21:15 by tdeverge          #+#    #+#             */
/*   Updated: 2023/02/15 11:10:29 by pmieuzet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_MINISHELL_H
# define STRUCT_MINISHELL_H

extern unsigned char	g_value;

/********************************************************/
/*					Environment							*/
/********************************************************/
typedef struct s_variable
{
	char				*name;
	char				*content;
	int					index;
	struct s_variable	*next;
}	t_variable;

typedef struct s_env
{
	t_variable	*var;
	char		**envp;
}	t_env;

/********************************************************/
/*					Tokens (pre-parsing)				*/
/********************************************************/
typedef struct s_token
{
	char			*arg;
	int				index;
	int				rule;
	struct s_token	*next;
}	t_token;

typedef struct s_parse
{
	t_token	*token;
}	t_parse;

/********************************************************/
/*					Commands (parsing)					*/
/********************************************************/
typedef struct s_command
{
	char				**cmd;
	char				**redi;
	int					fds[2];
	int					fdout;
	int					index;
	struct s_command	*next;
}	t_command;

typedef struct s_list
{
	pid_t		*pid;
	int			nb_cmd;
	t_command	*first;
}	t_list;

/********************************************************/
/*					Built-in (singleton)				*/
/********************************************************/
typedef struct s_builtins
{
	char	*name;
	int		(*f)(t_command *command, t_env *env);
}			t_builtins;

#endif
