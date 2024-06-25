/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert_matrix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 01:00:01 by tdeverge          #+#    #+#             */
/*   Updated: 2023/02/13 01:12:40 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @summary:
 * 		- Loop through matrice and count number of strings
 * 		it contains.
*/
static int	count_word_matrice(char **matrice)
{
	int	i;

	if (!matrice)
		return (0);
	i = 0;
	while (matrice[i])
		i++;
	return (i + 1);
}

/*
 * @summary
 * 		- Allocate dynamically a new matrice with the old matrice passed
 * 		as parameter + the string 'str' passed as parameter.
 * 		- Passed by reference all internal strings from old matrice and 
 * 		duplicate 'str' passed by parameter.
*/
char	**ft_insert_matrix(char **matrice, char *str)
{
	char	**new_matrice;
	int		matrice_len;
	int		i;

	i = 0;
	matrice_len = count_word_matrice(matrice) + 1;
	new_matrice = malloc(sizeof(char *) * (matrice_len + 1));
	if (!new_matrice)
		return (NULL);
	while (matrice && matrice[i])
	{
		new_matrice[i] = matrice[i];
		i++;
	}
	new_matrice[i++] = ft_strdup(str);
	new_matrice[i] = 0;
	if (matrice)
		free(matrice);
	return (new_matrice);
}
