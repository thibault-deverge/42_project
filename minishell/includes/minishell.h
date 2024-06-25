/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 17:57:08 by tdeverge          #+#    #+#             */
/*   Updated: 2023/02/13 03:30:40 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*		Libft				*/
# include "../libft/includes/libft.h"
/*		Standard Library	*/
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <signal.h>
# include <errno.h>
/*		POSIX Api			*/
# include <unistd.h>
# include <fcntl.h>
/*		GNU Library			*/
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
/*		Minishell			*/
# include "macro_minishell.h"
# include "struct_minishell.h"
# include "prototype_minishell.h"

#endif
