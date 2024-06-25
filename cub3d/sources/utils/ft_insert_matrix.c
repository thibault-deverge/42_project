/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert_matrix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 01:00:01 by tdeverge          #+#    #+#             */
/*   Updated: 2023/04/21 18:53:39 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
 * @summary:
 * 		- Loop through matrix and count number of strings
 * 		it contains.
*/
static int	count_word_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return (0);
	i = 0;
	while (matrix[i])
		i++;
	return (i + 1);
}

static void	*handle_error(char **old, char **new)
{
	free(old);
	free_matrix(new);
	return (NULL);
}

/*
 * @summary
 * 		- Allocate dynamically a new matrix with the old matrix passed
 * 		as parameter + the string 'str' passed as parameter.
 * 		- Passed by reference all internal strings from old matrix and 
 * 		duplicate 'str' passed by parameter.
*/
char	**ft_insert_matrix(char **matrix, char *str)
{
	char	**new_matrix;
	int		matrix_len;
	int		i;

	i = 0;
	matrix_len = count_word_matrix(matrix) + 1;
	new_matrix = malloc(sizeof(char *) * (matrix_len + 1));
	if (!new_matrix)
	{
		free_matrix(matrix);
		return (NULL);
	}
	while (matrix && matrix[i])
	{
		new_matrix[i] = matrix[i];
		i++;
	}
	new_matrix[i] = ft_strdup(str);
	if (!new_matrix[i])
		return (handle_error(matrix, new_matrix));
	i++;
	new_matrix[i] = 0;
	if (matrix)
		free(matrix);
	return (new_matrix);
}
