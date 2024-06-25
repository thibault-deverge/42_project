/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 17:57:58 by tdeverge          #+#    #+#             */
/*   Updated: 2022/12/11 16:34:40 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_arg_nb(int argc)
{
	if (argc != 2)
		return (0);
	return (1);
}

static int	check_arg_ext(char *argv)
{
	size_t	arg_len;
	size_t	i;

	arg_len = ft_strlen(argv);
	i = arg_len - 4;
	if (ft_strncmp(&argv[i], ".ber", 4))
		return (0);
	if (!argv[i - 1] || argv[i - 1] == '/')
		return (0);
	return (1);
}

/*
 * @summary:
 * 		- Check if there is only one argument and extension of map is .ber
*/
void	check_arg(int argc, char *argv)
{
	if (!check_arg_nb(argc))
		throw_error_personalized(WRONG_ARGS);
	if (!check_arg_ext(argv))
		throw_error_personalized(WRONG_EXT);
}
