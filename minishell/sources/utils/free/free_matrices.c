/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_matrices.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 02:50:35 by tdeverge          #+#    #+#             */
/*   Updated: 2023/02/13 02:51:10 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @summary:
 * 		- Free both matrices passed as parameter.
*/
void	free_matrices(char **matrix1, char **matrix2)
{
	free_matrix(matrix1);
	free_matrix(matrix2);
}

/*
 * @summary:
 * 		- Iterate throught the matrice and free every strings it contains.
 * 		- Free the matrice itself.
*/
void	free_matrix(char **matrice)
{
	int	i;

	i = 0;
	if (!matrice)
		return ;
	while (matrice[i])
	{
		free(matrice[i]);
		i++;
	}
	free(matrice);
}
