/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:30:21 by tdeverge          #+#    #+#             */
/*   Updated: 2023/02/12 21:30:23 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @summary:
 * 		- Display error message passed via errno variable, free environment, clear
 * 		history and exit with the value of global variable.
*/
static void	throw_perror_prompt(t_env *env)
{
	perror("error");
	free_env(env->var);
	rl_clear_history();
	g_value = 1;
	exit(g_value);
}

/*
 * @summary:
 * 		- Display error message passed as parameter, free prompt and clear
 * 		history then exit with the value of global variable.
*/
static void	throw_error_prompt(char *err_msg, char *prompt, t_env *env)
{
	ft_putstr_fd(err_msg, 1);
	free_env(env->var);
	free(prompt);
	rl_clear_history();
	exit(g_value);
}

/*
 * @summary:
 * 		- Join name of our team with the working directory and use it
 * 		as a prompt.
*/
static char	*get_prompt(void)
{
	char	*pwd;
	char	pwd_buf[1024];
	char	*custom_prompt;

	if (!getcwd(pwd_buf, PATH_SIZE))
		return (RETURN_FAILURE);
	pwd = ft_strjoin(pwd_buf, "$ ");
	if (!pwd)
		return (RETURN_FAILURE);
	custom_prompt = ft_strjoin("DREAMTEAM:", pwd);
	free(pwd);
	return (custom_prompt);
}

/*
 * @summary:
 * 		- Check if command is empty or only contains whitespaces.
*/
int	is_empty_input(char *cmd)
{
	size_t	i;

	i = 0;
	while (cmd && cmd[i] && ft_is_whitespace(cmd[i]))
		i++;
	if (ft_strlen(cmd) == i)
	{
		free(cmd);
		cmd = NULL;
		return (1);
	}
	return (0);
}

/*
 * @summary:
 * 		- Display prompt to user and ask for an input. Check for empty
 * 		input and add to history if command exists.
*/
char	*get_input(t_env *env)
{
	char	*command;
	char	*prompt;

	prompt = get_prompt();
	if (prompt == RETURN_FAILURE)
		throw_perror_prompt(env);
	command = readline(prompt);
	if (!command)
		throw_error_prompt(ERROR_PROMPT, prompt, env);
	if (command[0])
		add_history(command);
	free(prompt);
	return (command);
}
