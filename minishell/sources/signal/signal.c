/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 03:17:27 by tdeverge          #+#    #+#             */
/*   Updated: 2023/02/13 17:27:54 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @summary:
 * 		- Handle SIGINT by sending a new prompt to the user.
*/
static void	sigint_handler_prompt(int sig_id)
{
	(void)sig_id;
	g_value = 130;
	ft_putchar_fd('\n', 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

/*
 * summary:
 * 		- Handle SIGINT by sending a new prompt in a blocking command
 * 		like 'cat'.
*/
static void	sigint_handler_cmd(int sig_id)
{
	(void)sig_id;
	g_value = 130;
	ft_putchar_fd('\n', 1);
}

/*
 * @summary:
 * 		- Handle SIGINT in heredoc by closing stdin and redisplay a new
 * 		prompt.
*/
static void	sigint_handler_heredoc(int sig_id)
{
	(void)sig_id;
	close(0);
	g_value = 130;
	ft_putchar_fd('\n', 1);
	rl_redisplay();
}

/*
 * @summary:
 *		- Handle SIGKILL by sending a message and displaying a new prompt
 *		in a blocking command like 'cat'.
*/
static void	sigkill_handler_cmd(int sig_id)
{
	(void)sig_id;
	ft_putstr_fd("Quit (core dumped)\n", 1);
	g_value = 131;
}

/*
 * @summary:
 * 		- Main function to handle signals. It will change
 * 		the behavior of SIGINT and SIGQUIT depend where signal 
 * 		is received in the program.
*/
void	modify_signals(int behavior)
{
	if (behavior == PROMPT_SIGNAL)
	{
		signal(SIGINT, &sigint_handler_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (behavior == CMD_SIGNAL)
	{
		signal(SIGINT, &sigint_handler_cmd);
		signal(SIGQUIT, &sigkill_handler_cmd);
	}
	else if (behavior == FORK_SIGNAL)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (behavior == HEREDOC_SIGNAL)
	{
		signal(SIGINT, &sigint_handler_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
}
